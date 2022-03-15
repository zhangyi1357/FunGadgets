#ifndef _VECTOR_H_
#define _VECTOR_H_

template <typename T>
class Vector {
public:
    Vector() { ReAlloc(2); }

    void PushBack(const T& value) {
        // check the space
        if (m_Size >= m_Capacity)
            ReAlloc(m_Size + m_Size);

        // push the value back and update the size
        m_Data[m_Size++] = value;
    }

    T& operator[](size_t index) { return m_Data[index]; }
    const T& operator[](size_t index) const { return m_Data[index]; }

    size_t Size() const { return m_Size; }

private:
    void ReAlloc(size_t newCapacity) {
        // allocate space for new block
        T* newBlock = new T[newCapacity];

        // ensure no overflow
        if (newCapacity < m_Size)
            m_Size = newCapacity;

        // move all the elements to the new block
        for (int i = 0; i < m_Size; ++i)
            newBlock[i] = m_Data[i];

        // delete the old space and update old members
        delete[] m_Data;
        m_Data = newBlock;
        m_Capacity = newCapacity;
    }

private:
    T* m_Data = nullptr;

    size_t m_Size = 0;
    size_t m_Capacity = 0;
};


#endif  // !_VECTOR_H_