#ifndef MAIN_CPP_VECTORITERATOR_H
#define MAIN_CPP_VECTORITERATOR_H

template <class T>
class VectorIterator
{
public:
    VectorIterator(T* ptr)
            : m_Ptr(ptr){}

    VectorIterator& operator++()
    {
        m_Ptr ++;
        return *this;
    }

    VectorIterator operator++(int)
    {
        VectorIterator<T> temp = *this;
        ++(*this);
        return temp;
    }

    VectorIterator& operator--()
    {
        m_Ptr --;
        return *this;
    }

    VectorIterator operator--(int)
    {
        VectorIterator<T> temp = *this;
        --(*this);
        return temp;
    }

    VectorIterator& operator =(const VectorIterator<T>& other)
    {
        if (this != &other)
            m_Ptr = other.m_Ptr;
        return *this;
    }

    bool operator ==(const VectorIterator<T>& other) const
    {
        return (m_Ptr == other.m_Ptr);
    }

    bool operator !=(const VectorIterator<T>& other) const
    {
        return (m_Ptr != other.m_Ptr);
    }

    T& operator*()
    {
        return *m_Ptr;
    }

private:
    T* m_Ptr;

};

#endif
