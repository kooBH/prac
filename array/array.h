#ifndef IIPLAB_ARRAY_H
#define IIPLAB_ARRAY_H

#include <stdio.h>

#include <algorithm>
#include <assert.h>
#include <stddef.h>


#include <cmath>
#include <complex>

using sfloat_t = double;

#ifdef _WIN32
#define ALIGNOF(x) __alignof(x)
#define ALIGNAS(x) __declspec(align(x))
#define THREAD_LOCAL __declspec(thread)
#else
#define ALIGNOF(x) alignof(x)
#define ALIGNAS(x) alignas(x)
#define THREAD_LOCAL thread_local
#endif

inline sfloat_t fms(sfloat_t a, sfloat_t b, sfloat_t c) {
  return std::fma(a, b, -c);
}

#include <errno.h>
#include <stdint.h>
#include <unistd.h>


void *aligned_malloc(size_t alignment, size_t size);
void aligned_free(void *ptr);

/**************** array_view ********************/

template <typename T, size_t Dims> class array_view {
  const size_t *m_shape;
  T *m_begin;

public:
  array_view(const size_t *shape, T *begin) : m_shape(shape), m_begin(begin) {
//    printf("array_view constructor\n");
  }

  size_t shape(size_t idx) {
    printf("shape %lu\n",idx);
    if (idx == Dims - 1) {
      return m_shape[idx];
    }
    return m_shape[idx] / m_shape[idx + 1];
  }

  array_view<T, Dims - 1> operator[](size_t idx) {
  //  printf("array_vew 1 [%lu]\n",idx);
    return array_view<T, Dims - 1>(m_shape + 1, m_begin + m_shape[1] * idx);
  }

  array_view<const T, Dims - 1> operator[](size_t idx) const {
    printf("array_vew 2\n");
    return array_view<const T, Dims - 1>(m_shape + 1,
                                         m_begin + m_shape[1] * idx);
  }

  T *data() { return m_begin; }
  T *data() const { return m_begin; }
};

/********************** array_view *****************/

template <typename T> class array_view<T, 1> {
  size_t m_size;
  T *m_begin;

public:
  array_view(const size_t *shape, T *begin)
      : m_size(shape[0]), m_begin(begin) {}

  size_t shape(size_t) { return m_size; }

  T &operator[](size_t idx) { 
   // printf("array_view <1> [%lu]\n",idx);
    return m_begin[idx];
  }

  T const &operator[](size_t idx) const { return m_begin[idx]; }

  T *data() { return m_begin; }
  T *data() const { return m_begin; }
};


/************************ simd_array 1 *****************/

template <typename T, size_t Dims> class simd_array {
  size_t m_shape[Dims] = {};
  T *m_data;

public:
  simd_array() : m_data(nullptr) {
    printf("simd_array : constructor 0\n");
  }

  simd_array(std::initializer_list<size_t> shape, T const &val) {
    printf("simd_array : constructor 1\n");
    size_t size = 1;
    for (int dim = Dims - 1; dim >= 0; --dim) {
      size *= *(shape.begin() + dim);
      m_shape[dim] = size;
    }
    m_data = static_cast<T *>(aligned_malloc(ALIGNOF(T), sizeof(T) * size));
    for (size_t i = 0; i < size; ++i) {
      new (&m_data[i]) T(val);
    }
  }

  simd_array(std::initializer_list<size_t> shape) {
    printf("simd_array : constructor 2\n");
    size_t size = 1;
    for (int dim = Dims - 1; dim >= 0; --dim) {
      size *= *(shape.begin() + dim);
      printf("size : %lu\n",size);
      m_shape[dim] = size;
    }
    m_data = static_cast<T *>(aligned_malloc(ALIGNOF(T), sizeof(T) * size));
    for (size_t i = 0; i < size; ++i) {
      new (&m_data[i]) T;
    }
  }

  simd_array(simd_array const &other) {
    printf("simd_array : constructor 3\n");
    std::copy(other.m_shape, other.m_shape + Dims, m_shape);
    m_data =
        static_cast<T *>(aligned_malloc(ALIGNOF(T), sizeof(T) * m_shape[0]));
    for (size_t i = 0; i < m_shape[0]; ++i) {
      new (&m_data[i]) T(other.m_data[i]);
    }
  }

  simd_array &operator=(simd_array const &other) {
    if (this == &other) {
      return *this;
    }
    if (m_shape[0] != other.m_shape[0]) {
      aligned_free(m_data);
      std::copy(other.m_shape, other.m_shape + Dims, m_shape);
      m_data =
          static_cast<T *>(aligned_malloc(ALIGNOF(T), sizeof(T) * m_shape[0]));
      for (size_t i = 0; i < m_shape[0]; ++i) {
        new (&m_data[i]) T(other.m_data[i]);
      }
    } else {
      std::copy(other.m_data, other.m_data + m_shape[0], m_data);
    }
    return *this;
  }

  simd_array &operator=(simd_array &&other) {
    std::copy(other.m_shape, other.m_shape + Dims, m_shape);
    m_data = other.m_data;
    other.m_data = nullptr;
    return *this;
  }

  ~simd_array() { aligned_free(m_data); }

  size_t shape(size_t idx) const {
    if (idx == Dims - 1) {
      return m_shape[idx];
    }
    return m_shape[idx] / m_shape[idx + 1];
  }

  array_view<T, Dims - 1> operator[](size_t idx) {
  //  printf("call array_view 1 [%lu]\n",idx);
    return array_view<T, Dims - 1>(m_shape + 1, m_data + m_shape[1] * idx);
  }
  array_view<const T, Dims - 1> operator[](size_t idx) const {
  //  printf("call array_view 2\n");
    return array_view<const T, Dims - 1>(m_shape + 1,
                                         m_data + m_shape[1] * idx);
  }

  T *data() { return m_data; }
  T *data() const { return m_data; }
};


/************************ simd_array 2 *****************/

template <typename T> class simd_array<T, 1> {
  size_t m_size;
  T *m_data;

public:
  simd_array() : m_size(0), m_data(nullptr) {
    printf("simd_array : constructor 0\n");
  }

  simd_array(std::initializer_list<size_t> shape, T const &val) {
    printf("simd_array : constructor 1\n");
    m_size = *shape.begin();
    m_data = static_cast<T *>(aligned_malloc(ALIGNOF(T), sizeof(T) * m_size));
    for (size_t i = 0; i < m_size; ++i) {
      new (&m_data[i]) T(val);
    }
  }

  simd_array(std::initializer_list<size_t> shape) {
    printf("simd_array : constructor 2\n");
    m_size = *shape.begin();
    m_data = static_cast<T *>(aligned_malloc(ALIGNOF(T), sizeof(T) * m_size));
    for (size_t i = 0; i < m_size; ++i) {
      new (&m_data[i]) T;
    }
  }

  simd_array(simd_array const &other)
      : m_size(other.m_size),
        m_data(
            static_cast<T *>(aligned_malloc(ALIGNOF(T), sizeof(T) * m_size))) {
    printf("simd_array : constructor 3\n");
    std::copy(other.m_data, other.m_data + m_size, m_data);
  }

  simd_array &operator=(simd_array const &other) {
    if (this == &other) {
      return *this;
    }
    if (m_size != other.m_size) {
      aligned_free(m_data);
      m_size = other.m_size;
      m_data = static_cast<T *>(aligned_malloc(ALIGNOF(T), sizeof(T) * m_size));
      for (size_t i = 0; i < m_size; ++i) {
        new (&m_data[i]) T(other.m_data[i]);
      }
    } else {
      std::copy(other.m_data, other.m_data + m_size, m_data);
    }
    return *this;
  }

  simd_array &operator=(simd_array &&other) {
    m_size = other.m_size;
    m_data = other.m_data;
    other.m_data = nullptr;
    return *this;
  }

  simd_array &operator=(array_view<T, 1> other) {
    if (m_size != other.shape(0)) {
      aligned_free(m_data);
      m_size = other.shape(0);
      m_data = static_cast<T *>(aligned_malloc(ALIGNOF(T), sizeof(T) * m_size));
      for (size_t i = 0; i < m_size; ++i) {
        new (&m_data[i]) T(other[i]);
      }
    }
    std::copy(other.data(), other.data() + m_size, m_data);
    return *this;
  }

  ~simd_array() { aligned_free(m_data); }

  operator array_view<T, 1>() { return array_view<T, 1>(&m_size, m_data); }

  operator array_view<T, 1>() const {
    return array_view<const T, 1>(&m_size, m_data);
  }

  size_t shape(size_t) const { return m_size; }

  T &operator[](size_t idx) { return m_data[idx]; }
  T const &operator[](size_t idx) const { return m_data[idx]; }

  T *data() { return m_data; }
  T *data() const { return m_data; }
};

/********************** memory.cpp ********************/
void *aligned_malloc(size_t alignment, size_t size) {
  printf("%s (%lu,%lu)\n",__func__,alignment,size);
  void *result;
  alignment = std::max(sizeof(void *), alignment);
  size = size + size % alignment;
  int status = posix_memalign(&result, alignment, size);
  if (status == EINVAL || status == ENOMEM) {
    exit(status);
  }
  if (uintptr_t(result) % alignment) {
    exit(-1);
  }
#ifndef NDEBUG
//  printf("Allocated %d bytes aligned %d bytes\n", int(alignment), int(size));
#endif
  return result;
}

void aligned_free(void *ptr) { free(ptr); }

#elif _WIN32

#include <malloc.h>

void *aligned_malloc(size_t alignment, size_t size) {
  alignment = std::max(sizeof(void *), alignment);
  return _aligned_malloc(size, alignment);
}

void aligned_free(void *ptr) { _aligned_free(ptr); }



#endif
