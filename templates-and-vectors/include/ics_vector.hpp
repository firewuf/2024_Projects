#ifndef ICS_VECTOR_H
#define ICS_VECTOR_H

#include "vector_exception.hpp"
#include <iosfwd>

template <typename T>
class Vector
{
    size_t v_capacity;
    size_t v_size;
    T *buffer;
    class Iterator
    {
        Vector *vector;
        size_t index;

    public:
        Iterator(Vector *vector, size_t index = 0)
        {
            this->vector = vector;
            this->index = index;
        }

        // prefix
        Iterator operator++()
        {
            if (index == vector->v_size)
                throw VectorException("out of bounds");

            ++index;

            return *this;
        }

        // postfix
        Iterator operator++(int)
        {
            if (index == vector->v_size)
                throw VectorException("out of bounds");

            Iterator temp = Iterator(this->vector, this->index);

            ++index;

            return temp;
        }

        Iterator operator--()
        {
            if (index == 0)
                throw VectorException("out of bounds");

            --index;

            return *this;
        }

        Iterator operator--(int)
        {
            if (index == 0)
                throw VectorException("out of bounds");

            Iterator temp = Iterator(this->vector, this->index);

            --index;

            return temp;
        }

        bool operator==(const Iterator &other) const noexcept
        {
            return ((this->vector == other.vector) && (this->index == other.index));
        }

        bool operator!=(const Iterator &other) const noexcept
        {
            return !((this->vector == other.vector) && (this->index == other.index));
        }

        T &operator*() const
        {
            if (index >= vector->v_size)
                throw VectorException("out of bounds");
            return vector->buffer[index];
        }

        T *operator->() const
        {
            if (index >= vector->v_size)
                throw VectorException("out of bounds");
            return &vector->buffer[index];
        }

        size_t operator-(const Iterator &other) const
        {
            if (this->vector != other.vector)
                throw VectorException("iterators point to different containers");
            if (static_cast<int>(this->index) - static_cast<int>(other.index) < 0)
                throw VectorException("out of bounds");
            return size_t(abs(this->index - other.index));
        }

        Iterator operator-(size_t offset) const
        {
            if (static_cast<int>(index) - static_cast<int>(offset) < 0)
                throw VectorException("out of bounds");
            size_t newIndex;
            if (offset >= index)
                newIndex = 0;
            else
                newIndex = index - offset;

            return Iterator(this->vector, newIndex);
        }

        Iterator &operator+=(size_t offset)
        {
            if (index + offset > vector->v_size)
                throw VectorException("out of bounds");
            index += offset;

            return *this;
        }

        Iterator &operator-=(size_t offset)
        {
            if (static_cast<int>(index) - static_cast<int>(offset) < 0)
                throw VectorException("out of bounds");
            if (offset >= index)
                index = 0;
            else
                index -= offset;

            return *this;
        }

        friend Iterator operator+(size_t s, const Iterator &iter)
        {
            if (iter.index + s > iter.vector->size())
                throw VectorException("out of bounds");
            Iterator retIter(iter.vector, iter.index + s);
            return retIter;
        }

        friend Iterator operator+(const Iterator &iter, size_t s)
        {
            if (iter.index + s > iter.vector->size())
                throw VectorException("out of bounds");
            Iterator retIter(iter.vector, iter.index + s);
            return retIter;
        }

        size_t getIndex()
        {
            return index;
        }
    };

    bool checkArrayEqual(const Vector &rhs) const
    {
        if (!buffer && !rhs.buffer)
            return true;
        else if (!buffer || !rhs.buffer)
            return false;

        if (v_size != rhs.v_size)
            return false;

        for (size_t i = 0; i < v_size; i++)
        {
            if (buffer[i] != rhs.buffer[i])
                return false;
        }

        return true;
    }

    void copyToNewArray(T *oldArr, T *newArr, size_t size)
    {
        for (size_t i = 0; i < size; i++)
        {
            newArr[i] = oldArr[i];
        }
    }

    void moveToNewArray(T *oldArr, T *newArr, size_t size)
    {
        for (size_t i = 0; i < size; i++)
        {
            newArr[i] = std::move(oldArr[i]);
        }
    }

public:
    Vector()
    {
        v_capacity = 0;
        v_size = 0;
        buffer = nullptr;
    }

    Vector(size_t capacity)
    {
        v_capacity = capacity;
        v_size = 0;
        buffer = new T[v_capacity];
    }

    // Copy constructor
    Vector(const Vector<T> &orig)
    {
        v_capacity = orig.v_capacity;
        v_size = orig.v_size;
        buffer = new T[v_capacity];

        for (int i = 0; i < static_cast<int>(orig.v_size); i++)
        {
            buffer[i] = orig[i];
        }
    }

    // Move constructor
    Vector(Vector<T> &&orig) noexcept
    {
        v_capacity = orig.v_capacity;
        v_size = orig.v_size;
        buffer = orig.buffer;

        orig.v_capacity = 0;
        orig.v_size = 0;
        orig.buffer = nullptr;
    }

    ~Vector()
    {
        clear();
        delete[] buffer;
    }

    Iterator begin() noexcept
    {
        return Iterator(this);
    }

    T const *begin() const noexcept
    {
        if (!v_size)
            return nullptr;
        return &buffer[0];
    }

    Iterator end() noexcept
    {
        return Iterator(this, v_size);
    }

    T const *end() const noexcept
    {
        if (v_size == v_capacity)
            return nullptr;
        return &buffer[v_size];
    }

    T &front() noexcept
    {
        return buffer[0];
    }

    T const &front() const noexcept
    {
        return buffer[0];
    }

    T &back() noexcept
    {
        return buffer[v_size - 1];
    }

    T const &back() const noexcept
    {
        return buffer[v_size - 1];
    }

    bool empty() const noexcept
    {
        return !v_size;
    }

    size_t size() const noexcept
    {
        return v_size;
    }

    size_t capacity() const noexcept
    {
        return v_capacity;
    }

    T *data() noexcept
    {
        return buffer;
    }

    T const *data() const noexcept
    {
        return buffer;
    }

    void push_back(const T &newValue)
    {
        if (v_size == v_capacity)
        {
            size_t newCapacity;
            if (v_capacity >= 1)
                newCapacity = v_capacity * 2;
            else
                newCapacity = 1;
            T *newBuffer = new T[newCapacity];
            moveToNewArray(buffer, newBuffer, v_size);
            newBuffer[v_size] = newValue;

            v_capacity = newCapacity;
            delete[] buffer;
            buffer = newBuffer;
        }
        else
        {
            buffer[v_size] = newValue;
        }
        v_size++;
    }

    void push_back(T &&newValue)
    {
        if (v_size == v_capacity)
        {
            size_t newCapacity;
            if (v_capacity >= 1)
                newCapacity = v_capacity * 2;
            else
                newCapacity = 1;
            T *newBuffer = new T[newCapacity];
            moveToNewArray(buffer, newBuffer, v_size);
            newBuffer[v_size] = std::move(newValue);

            v_capacity = newCapacity;
            delete[] buffer;
            buffer = newBuffer;
        }
        else
        {
            buffer[v_size] = std::move(newValue);
        }
        v_size++;
    }

    void pop_back()
    {
        if (!v_size)
            throw VectorException("popping from empty");

        buffer[v_size - 1].~T();

        v_size--;
    }

    void erase(Iterator start, Iterator end)
    {
        if (start == end)
            return;
        size_t diff = end - start;
        for (size_t i = start.getIndex(); i < v_size; i++)
        {
            buffer[i].~T();
            if (i + diff < v_size)
                buffer[i] = buffer[i + diff];
        }
        v_size -= diff;
    }

    void swap_elements(Iterator lhs, Iterator rhs) noexcept
    {
        T temp = std::move(buffer[lhs.getIndex()]);
        buffer[lhs.getIndex()] = std::move(buffer[rhs.getIndex()]);
        buffer[rhs.getIndex()] = std::move(temp);
    }

    Vector<T> &operator=(const Vector<T> &rhs) noexcept
    {
        v_size = rhs.v_size;
        clear();
        if (v_capacity < rhs.v_capacity)
        {
            v_capacity = rhs.v_capacity;
            delete[] buffer;
            buffer = new T[v_capacity];
        }
        copyToNewArray(rhs.buffer, buffer, v_size);
        return *this;
    }

    Vector<T> &operator=(Vector<T> &&rhs) noexcept
    {
        v_capacity = rhs.v_capacity;
        rhs.v_capacity = 0;
        v_size = rhs.v_size;
        rhs.v_size = 0;
        delete[] buffer;
        buffer = rhs.buffer;
        rhs.buffer = nullptr;
        return *this;
    }

    T &operator[](size_t index) noexcept
    {
        return buffer[index];
    }

    T const &operator[](size_t index) const noexcept
    {
        return buffer[index];
    }

    T &at(size_t index)
    {
        if (index >= v_size)
            throw VectorException("out of bounds");
        return buffer[index];
    }

    T const &at(size_t index) const
    {
        if (index >= v_size)
            throw VectorException("out of bounds");
        return buffer[index];
    }

    void resize(size_t new_capacity)
    {
        if (new_capacity == v_capacity)
            return;
        size_t new_size;
        if (v_size >= new_capacity)
            new_size = new_capacity;
        else
            new_size = v_size;
        T *newBuffer = new T[new_capacity];
        moveToNewArray(buffer, newBuffer, new_size);

        clear();
        delete[] buffer;
        buffer = newBuffer;
        v_size = new_size;
        v_capacity = new_capacity;
    }

    bool operator==(const Vector &other) const noexcept
    {
        return checkArrayEqual(other);
    }

    bool operator!=(const Vector &other) const noexcept
    {
        return !checkArrayEqual(other);
    }

    void clear() noexcept
    {
        for (int i = 0; i < static_cast<int>(v_size); i++)
        {
            buffer[i].~T();
        }
        v_size = 0;
    }

    friend std::ostream &operator<<(std::ostream &ostr, const Vector &vec)
    {
        for (size_t i = 0; i < vec.v_size; i++)
        {
            ostr << vec.buffer[i] << " ";
        }
        return ostr;
    }
};
#endif