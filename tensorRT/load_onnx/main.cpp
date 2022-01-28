#include <iostream>
#include <fstream>
#include <NvInfer.h>
#include <memory>
#include <NvOnnxParser.h>
#include <vector>
#include <cuda_runtime_api.h>


// reference : https://github.com/spmallick/learnopencv/blob/master/PyTorch-ONNX-TensorRT-CPP/trt_sample.cpp

// utilities ----------------------------------------------------------------------------------------------------------
// class to log errors, warnings, and other information during the build and inference phases
class Logger : public nvinfer1::ILogger
{
public:
  //void log(Severity severity, const char* msg) override {
  void log(Severity severity, const char* msg) noexcept override {
    // remove this 'if' if you need more logged info
    if ((severity == Severity::kERROR) || (severity == Severity::kINTERNAL_ERROR)) {
      std::cout << msg << "\n";
    }
  }
} gLogger;

// destroy TensorRT objects if something goes wrong
struct TRTDestroy
{
  template <class T>
  void operator()(T* obj) const
  {
    if (obj)
    {
      obj->destroy();
    }
  }
};

template <class T>
using TRTUniquePtr = std::unique_ptr<T, TRTDestroy>;

// calculate size of tensor
size_t getSizeByDim(const nvinfer1::Dims& dims)
{
  size_t size = 1;
  for (size_t i = 0; i < dims.nbDims; ++i)
  {
    size *= dims.d[i];
  }
  return size;
}

// initialize TensorRT engine and parse ONNX model --------------------------------------------------------------------
void parseOnnxModel(const std::string& model_path, TRTUniquePtr<nvinfer1::ICudaEngine>& engine,
  TRTUniquePtr<nvinfer1::IExecutionContext>& context)
{
  /* https://github.com/onnx/onnx-tensorrt/issues/266 
   "ONNX parser only supports networks with an explicit batch dimension"
   =>
  #crouchggj : 
  using following steps to create INetworkDefinition instance works for me:
  (1) const auto explicitBatch = 1U << static_cast<uint32_t>(nvinfer1::NetworkDefinitionCreationFlag::kEXPLICIT_BATCH);
  (2) auto network = GhUniquePtr(builder->createNetworkV2(explicitBatch));
   */
  const auto explicitBatch = 1U << static_cast<uint32_t>(nvinfer1::NetworkDefinitionCreationFlag::kEXPLICIT_BATCH);

  TRTUniquePtr<nvinfer1::IBuilder> builder{ nvinfer1::createInferBuilder(gLogger) };

  //TRTUniquePtr<nvinfer1::INetworkDefinition> network{ builder->createNetwork() };
  TRTUniquePtr<nvinfer1::INetworkDefinition> network{ builder->createNetworkV2(explicitBatch) };

  TRTUniquePtr<nvonnxparser::IParser> parser{ nvonnxparser::createParser(*network, gLogger) };
  TRTUniquePtr<nvinfer1::IBuilderConfig> config{ builder->createBuilderConfig() };
  // parse ONNX
  if (!parser->parseFromFile(model_path.c_str(), static_cast<int>(nvinfer1::ILogger::Severity::kINFO)))
  {
    std::cerr << "ERROR: could not parse the model.\n";
    return;
  }
  // allow TensorRT to use up to 1GB of GPU memory for tactic selection.
  config->setMaxWorkspaceSize(1ULL << 30);
  // use FP16 mode if possible
  if (builder->platformHasFastFp16())
  {
    config->setFlag(nvinfer1::BuilderFlag::kFP16);
  }
  // we have only one image in batch
  builder->setMaxBatchSize(1);
  // generate TensorRT engine optimized for the target platform
  engine.reset(builder->buildEngineWithConfig(*network, *config));
  context.reset(engine->createExecutionContext());
}

int main() {

  std::string model_path("../../test.onnx");
  int batch_size = 1;

  // initialize TensorRT engine and parse ONNX model
  TRTUniquePtr<nvinfer1::ICudaEngine> engine{ nullptr };
  TRTUniquePtr<nvinfer1::IExecutionContext> context{ nullptr };
  parseOnnxModel(model_path, engine, context);

  // get sizes of input and output and allocate memory required for input data and for output data
  std::vector<nvinfer1::Dims> input_dims; // we expect only one input
  std::vector<nvinfer1::Dims> output_dims; // and one output
  std::vector<void*> buffers(engine->getNbBindings()); // buffers for input and output data

  std::cout << "engine->getNbBindings() : " << engine->getNbBindings()<<std::endl;


  // allocate data
  for (size_t i = 0; i < engine->getNbBindings(); ++i)
  {
    std::cout << "engine->getBindingDimensions("<<i<<").nbDims : " << engine->getBindingDimensions(i).nbDims<<std::endl;
    auto binding_size = getSizeByDim(engine->getBindingDimensions(i)) * batch_size * sizeof(float);
    cudaMalloc(&buffers[i], binding_size);
    if (engine->bindingIsInput(i))
    {
      input_dims.emplace_back(engine->getBindingDimensions(i));
    }
    else
    {
      output_dims.emplace_back(engine->getBindingDimensions(i));
    }
  }
  if (input_dims.empty() || output_dims.empty())
  {
    std::cerr << "Expect at least one input and one output for network\n";
    return -1;
  }

  // inference
  context->enqueue(batch_size, buffers.data(), 0, nullptr);


  //void postprocessResults(float *gpu_output, const nvinfer1::Dims &dims, int batch_size)
  // copy results from GPU to CPU
  std::vector<float> cpu_output(getSizeByDim(output_dims[0]) * batch_size);
  cudaMemcpy(cpu_output.data(), (float*)buffers[1], cpu_output.size() * sizeof(float), cudaMemcpyDeviceToHost);

  std::cout << "output : "<<std::endl;
  std::cout << cpu_output[0]<<std::endl;
  std::cout << cpu_output[1]<<std::endl;
  std::cout << cpu_output[2]<<std::endl;

  // free
  for (void* buf : buffers)
  {
    cudaFree(buf);
  }

  return 0;
}