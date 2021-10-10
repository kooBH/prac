
#include "common.h"

struct BufferController {
  BYTE* bpBackupBuffer;
  unsigned long ulPushBytes;
  unsigned long ulPopBytes;
  unsigned long ulBufferSize;
};

bool isMicFrameOver = 0;
bool isRecordFinish = 0;
bool isSpeakerFrameOver = 0;
bool isCaptureFinish = 0;
bool bIsFirstFrame = 1;
unsigned long ulSpeakerTotalFrame = 0;
unsigned long ulSpeakerFrameCounter = 0;
unsigned long ulSpeakerSavedIndex = 0, ulSpeakerProcessedIndex = 0;
BufferController FarendBuffer, InputBuffer;

#define SAFE_RELEASE(punk)  \
              if ((punk) != NULL)  \
                { (punk)->Release(); (punk) = NULL; }

int main(int argc, char *argv[]) {


  HRESULT hr = S_OK;
  unsigned int channels, fs, bufferFrames, device = 0, offset = 0;
  double time = 2.0;
  FILE* fd;

  hr = CoInitialize(NULL);
  if (FAILED(hr)) {
    ERR(L"CoInitialize failed: hr = 0x%08x", hr);
    return -__LINE__;
  }
  CoUninitializeOnExit cuoe;

  // parse command line
  //CPrefs prefs(argc, argv, hr);
  CPrefs prefs(argc, NULL, hr);
  if (FAILED(hr)) {
    ERR(L"CPrefs::CPrefs constructor failed: hr = 0x%08x", hr);
    return -__LINE__;
  }
  if (S_FALSE == hr) {
    // nothing to do
    return 0;
  }

  // create a "loopback capture has started" event
  HANDLE hStartedEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
  if (NULL == hStartedEvent) {
    ERR(L"CreateEvent failed: last error is %u", GetLastError());
    return -__LINE__;
  }
  CloseHandleOnExit closeStartedEvent(hStartedEvent);

  // create a "stop capturing now" event
  HANDLE hStopEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
  if (NULL == hStopEvent) {
    ERR(L"CreateEvent failed: last error is %u", GetLastError());
    return -__LINE__;
  }
  CloseHandleOnExit closeStopEvent(hStopEvent);




  // create arguments for loopback capture thread
  LoopbackCaptureThreadFunctionArguments threadArgs;
  threadArgs.hr = E_UNEXPECTED; // thread will overwrite this
  threadArgs.pMMDevice = prefs.m_pMMDevice;
  threadArgs.bInt16 = 1;// prefs.m_bInt16;
  threadArgs.hFile = prefs.m_hFile;
  threadArgs.hStartedEvent = hStartedEvent;
  threadArgs.hStopEvent = hStopEvent;
  threadArgs.nFrames = 0;


  /* Start Endpoint Device Enumeration */
  unsigned int count;
  IMMDeviceEnumerator* pEnumerator = NULL;
  IMMDeviceCollection* pCollection = NULL;
  IMMDevice* pEndpoint = NULL;
  IPropertyStore* pProps = NULL;
  LPWSTR pwszID = NULL;

  const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
  const IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);


  hr = CoCreateInstance(
    CLSID_MMDeviceEnumerator, NULL,
    CLSCTX_ALL, IID_IMMDeviceEnumerator,
    (void**)&pEnumerator);

  hr = pEnumerator->EnumAudioEndpoints(
    eCapture, DEVICE_STATE_ACTIVE,
    &pCollection);
  hr = pEnumerator->EnumAudioEndpoints(
    eRender, DEVICE_STATE_ACTIVE,
    &pCollection);

  hr = pCollection->GetCount(&count);
  printf("count : %u\n", count);
  for (ULONG i = 0; i < count; i++)
  {
    // Get pointer to endpoint number i.
    hr = pCollection->Item(i, &pEndpoint);

    // Get the endpoint ID string.
    hr = pEndpoint->GetId(&pwszID);

    hr = pEndpoint->OpenPropertyStore(
      STGM_READ, &pProps);

    PROPVARIANT varName;
    // Initialize container for property value.
    PropVariantInit(&varName);

    // Get the endpoint's friendly-name property.
    hr = pProps->GetValue(PKEY_Device_FriendlyName, &varName);

    // Print endpoint friendly name and endpoint ID.
    printf("Endpoint %d: \"%S\" (%S)\n",
      i, varName.pwszVal, pwszID);

    CoTaskMemFree(pwszID);
    pwszID = NULL;
    PropVariantClear(&varName);
    SAFE_RELEASE(pProps)
      SAFE_RELEASE(pEndpoint)
  }

  /* End */
  return 0;
}