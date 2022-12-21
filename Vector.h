#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include "VectorIterator.h"

template <class T>
class Vector
{
public:
    Vector() = default;
    explicit Vector(int size);
    Vector(Vector<T>&& other);
    Vector(const Vector<T>& other);
    Vector(const std::initializer_list<T>& list);
    ~Vector();

    void reserve(int new_Capacity);

    T& operator[](int index);
    Vector& operator=(const Vector<T>& other);
    Vector& operator=(Vector<T>&& other);

    bool operator==(const Vector<T>& other);

    template <typename... Args>
    void emplace_back(Args&&... args);

    void push_back(const T& elem);
    void push_back(T&& elem);

    void insertAt(int index, const T& elem);
    void insertAt(int index, T&& elem);

    VectorIterator<T> begin();
    VectorIterator<T> end();

    int size() { return m_Size; }
    int capacity() { return m_Capacity; }

    void popBack();

    void print();


private:
    void clearData();
    void ReAlloc(int new_Capacity);

    T* m_Data = nullptr;
    int m_Capacity = 0;
    int m_Size = 0;
};

template <class T>
Vector<T>::Vector(const Vector<T>& other)
{
    m_Size = other.m_Size;
    m_Capacity = m_Size;
    m_Data = (T*) operator new(m_Size * sizeof(T));

    for (int i = 0; i < m_Size; i++)
        m_Data[i] = other.m_Data[i];
}

template <class T>
Vector<T>::Vector(Vector<T>&& other)
{
    m_Size = other.m_Size;
    m_Capacity = m_Size;
    m_Data = other.m_Data;

    other.m_Data = nullptr;
    other.m_Size = 0;
    other.m_Capacity = 0;
}

template <class T>
Vector<T>::Vector(int size)
{
    m_Data = (T*) operator new(size * sizeof(T));
    m_Capacity = size;
    m_Size = size;
}

template <class T>
Vector<T>::Vector(const std::initializer_list<T>& list)
{
    m_Capacity = list.size();
    m_Size = m_Capacity;
    m_Data = (T*) operator new(list.size() * sizeof(T));
    for (int i = 0; i < list.size(); i++)
        m_Data[i] = list.begin()[i];
}

template <class T>
Vector<T>::~Vector()
{
    clearData();
}

template <class T>
void Vector<T>::reserve(int new_Capacity)
{
    if (new_Capacity > m_Capacity)
        ReAlloc(new_Capacity);
}

template <class T>
T& Vector<T>::operator[](int index)
{
    if (index > 0 && index < m_Size)
        return m_Data[index];
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
    if (this != &other)
    {
        clearData();

        m_Size = other.m_Size;
        m_Capacity = m_Size;
        m_Data = (T*) operator new(m_Size * sizeof(T));

        for (int i = 0; i < m_Size; i++)
            m_Data[i] = other.m_Data[i];
    }

    return *this;
}

template <class T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other)
{
    if (this != &other)
    {
        clearData();

        m_Size = other.m_Size;
        m_Capacity = m_Size;
        m_Data = other.m_Data;

        other.m_Data = nullptr;
        other.m_Size = 0;
        other.m_Capacity = 0;
    }

    return *this;
}

template <class T>
bool Vector<T>::operator==(const Vector<T>& other)
{
    if (m_Size != other.m_Size)
        return false;

    for (int i = 0; i < other.m_Size; i++)
        if (m_Data[i] != other.m_Data[i])
            return false;


    return true;
}

template <class T>
template <typename... Args>
void Vector<T>::emplace_back(Args&&... args)
{
    if (m_Size >= m_Capacity)
        this->ReAlloc(std::max(m_Capacity + 1, m_Capacity * 2));

    new(&m_Data[m_Size++]) T(std::forward<Args>(args)...);
}

template <class T>
void Vector<T>::push_back(const T& elem)
{
    if (m_Size >= m_Capacity)
        this->ReAlloc(std::max(m_Capacity + 1, m_Capacity * 2));

    m_Data[m_Size++] = elem;
}

template <class T>
void Vector<T>::push_back(T&& elem)
{
    if (m_Size >= m_Capacity)
        this->ReAlloc(std::max(m_Capacity + 1, m_Capacity * 2));

    m_Data[m_Size++] = std::move(elem);
}

template <class T>
void Vector<T>::insertAt(int index, const T& elem)
{
    if (index < 0 || index > m_Size)
        return;

    int new_Capacity = m_Capacity;
    while (m_Size >= new_Capacity)
        new_Capacity += std::max(new_Capacity, 1);

    T* new_Data = (T*) operator new(new_Capacity * sizeof(T));

    for (int i = 0; i < m_Size; i++)
        if (i < index)
            new_Data[i] = std::move(m_Data[i]);
        else
            new_Data[i + 1] = std::move(m_Data[i]);

    new_Data[index] = elem;

    clearData();

    m_Capacity = new_Capacity;
    m_Data = new_Data;
    m_Size++;
}

template <class T>
void Vector<T>::insertAt(int index, T&& elem)
{
    if (index < 0 || index > m_Size)
        return;

    int new_Capacity = m_Capacity;
    while (m_Size >= new_Capacity)
        new_Capacity += std::max(1, new_Capacity);

    T* new_Data = (T*) operator new(new_Capacity * sizeof(T));

    for (int i = 0; i < m_Size; i++)
        if (i < index)
            new_Data[i] = std::move(m_Data[i]);
        else
            new_Data[i + 1] = std::move(m_Data[i]);

    new_Data[index] = std::move(elem);

    clearData();

    m_Capacity = new_Capacity;
    m_Data = new_Data;
    m_Size++;
}

template <class T>
VectorIterator<T> Vector<T>::begin()
{
    return VectorIterator<T>(&m_Data[0]);
}

template <class T>
VectorIterator<T> Vector<T>::end()
{
    return VectorIterator<T>(&m_Data[m_Size]);
}

template <class T>
void Vector<T>::popBack()
{
    if (m_Size > 0)
    {
        m_Size--;
        m_Data[m_Size].~T();
    }
}

template <class T>
void Vector<T>::clearData()
{
    for (int i = 0; i < m_Size; i++)
        m_Data[i].~T();

    operator delete(m_Data, m_Capacity * sizeof(T));
}

template <class T>
void Vector<T>::ReAlloc(int new_Capacity)
{
    T* new_Data = (T*) operator new(new_Capacity * sizeof(T));

    for (int i = 0; i < std::min(new_Capacity, m_Size); i++)
        new_Data[i] = std::move(m_Data[i]);

    clearData();

    m_Size = std::min(new_Capacity, m_Size);
    m_Data = new_Data;
    m_Capacity = new_Capacity;
}

template <class T>
void Vector<T>::print()
{
    for (int i = 0; i < m_Size; i++)
        std::cout << m_Data[i] << " ";
    std::cout << std::endl;
}


#endif
