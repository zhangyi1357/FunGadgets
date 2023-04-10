#ifndef _ARRAY_H_
#define _ARRAY_H_

#include <cstddef>

template <typename T, size_t S> class Array {
  public:
    constexpr int Size() const { return S; }

    T &operator[](size_t index) { return m_Data[index]; }
    const T &operator[](size_t index) const { return m_Data[index]; }

    T *Data() { return m_Data; }
    const T *Data() const { return m_Data; }

  private:
    T m_Data[S];
};

#endif // !_ARRAY_H_