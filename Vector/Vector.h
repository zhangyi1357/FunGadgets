#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stddef.h>
#include <utility>

template <typename T> class Vector {
  public:
    Vector() { ReAlloc(2); }
    ~Vector() {
        Clear();
        ::operator delete(m_Data, m_Capacity * sizeof(T));
    }

    void PushBack(const T &value) {
        // check the space
        if (m_Size >= m_Capacity)
            ReAlloc(m_Size + m_Size);

        // push the value back and update the size
        m_Data[m_Size++] = value;
    }

    void PushBack(T &&value) {
        // check the space
        if (m_Size >= m_Capacity)
            ReAlloc(m_Size + m_Size);

        // push the value back and update the size
        m_Data[m_Size++] = std::move(value);
    }

    template <typename... Args> T &EmplaceBack(Args &&...args) {
        // check the space
        if (m_Size >= m_Capacity)
            ReAlloc(m_Size + m_Size);

        // Placement new
        new (&m_Data[m_Size]) T(std::forward<Args>(args)...);
        return m_Data[m_Size++];
    }

    void PopBack() {
        if (m_Size > 0) {
            --m_Size;
            m_Data[m_Size].~T();
        }
    }

    void Clear() {
        for (int i = 0; i < m_Size; ++i)
            m_Data[i].~T();

        m_Size = 0;
    }

    T &operator[](size_t index) { return m_Data[index]; }
    const T &operator[](size_t index) const { return m_Data[index]; }

    size_t Size() const { return m_Size; }

  private:
    void ReAlloc(size_t newCapacity) {
        // allocate space for new block
        T *newBlock = (T *)::operator new(newCapacity * sizeof(T));

        // ensure no overflow
        if (newCapacity < m_Size)
            m_Size = newCapacity;

        // move all the elements to the new block
        for (int i = 0; i < m_Size; ++i)
            new (&newBlock[i]) T(std::move(m_Data[i]));

        // delete the old space and update old members
        Clear();
        ::operator delete(m_Data, m_Capacity * sizeof(T));
        m_Data = newBlock;
        m_Capacity = newCapacity;
    }

  private:
    T *m_Data = nullptr;

    size_t m_Size = 0;
    size_t m_Capacity = 0;
};

#endif // !_VECTOR_H_