#pragma once

#include <initializer_list>
#include <new>
#include <cstdlib>

#include "Utility.h"

// TODO:
// * add a lambda based map

namespace SD {

template<typename VecType, typename ElementType>
class VecIterator {
public:
    bool operator!=(const VecIterator& other) const { return m_index != other.m_index; }
    bool operator==(const VecIterator& other) const { return m_index == other.m_index; }
    bool operator<(const VecIterator& other) const { return m_index < other.m_index; }
    bool operator>(const VecIterator& other) const { return m_index > other.m_index; }
    bool operator>=(const VecIterator& other) const { return m_index >= other.m_index; }
    VecIterator& operator++()
    {
        ++m_index;
        return *this;
    }
    VecIterator& operator--()
    {
        --m_index;
        return *this;
    }
    VecIterator operator-(size_t value) { return { m_vector, m_index - value }; }
    VecIterator operator+(size_t value) { return { m_vector, m_index + value }; }
    VecIterator& operator=(const VecIterator& other)
    {
        m_index = other.m_index;
        return *this;
    }
    ElementType& operator*() { return m_vector[m_index]; }
    size_t operator-(const VecIterator& other) { return m_index - other.m_index; }

    [[nodiscard]] bool is_end() const { return m_index == m_vector.size(); }
    [[nodiscard]] size_t index() const { return m_index; }

private:
    friend VecType;
    VecIterator(VecType& vector, size_t index)
        : m_vector(vector)
        , m_index(index)
    {
    }
    VecType& m_vector;
    size_t m_index { 0 };
};

template<typename T>
class Vec {
public:
    static Vec with_capacity(size_t size, T default_value)
    {
        Vec tmp;
        tmp.ensure_capacity(size);
        for(size_t i = 0; i < size; ++i) {
            tmp.unchecked_append(default_value);
        }
        return tmp;
    }

    Vec() = default;
    Vec(std::initializer_list<T> list)
    {
        ensure_capacity(list.size());
        for (auto& item : list)
            unchecked_append(item);
    }
    ~Vec() { clear(); }
    Vec(const Vec& other)
    {
        ensure_capacity(other.size());
        for (size_t i = 0; i < other.size(); ++i)
            new (slot(i)) T(other.at(i));
        m_size = other.size();
    }
    Vec(Vec&& other)
        : m_size(other.m_size)
        , m_capacity(other.m_capacity)
        , m_data(other.m_data)
    {
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }
    // TODO: Copy assignment ctor
    // TODO: Swap semantics

    size_t capacity() const { return m_capacity; }
    size_t size() const { return m_size; }
    T* data() { return m_data; }
    const T* data() const { return m_data; }

    inline T& at(size_t index)
    {
        ASSERT(index < size());
        return data()[index];
    }
    inline const T& at(size_t i) const
    {
        ASSERT(i < size());
        return data()[i];
    }
    inline const T& operator[](size_t i) const { return at(i); }
    inline T& operator[](size_t i) { return at(i); }

    const T& first() const { return at(0); }
    T& first() { return at(0); }
    const T& second() const { return at(1); }
    T& second() { return at(1); }
    const T& third() const { return at(2); }
    T& third() { return at(2); }

    const T& last() const { return at(size() - 1); }
    T& last() { return at(size() - 1); }

    bool is_empty() const { return size() == 0; }

    bool contains_slow(const T& value) const
    {
        for (size_t i = 0; i < size(); ++i) {
            if (at(i) == value)
                return true;
        }
        return false;
    }

    void unchecked_append(T&& value)
    {
        ASSERT((size() + 1) <= capacity());
        new (slot(m_size)) T(move(value));
        ++m_size;
    }

    void unchecked_append(const T& value)
    {
        unchecked_append(T(value));
    }

    void append(T&& value)
    {
        grow_capacity(size() + 1);
        new (slot(m_size)) T(move(value));
        ++m_size;
    }

    void append(const T& value)
    {
        append(T(value));
    }

    //
    // Storage
    //
    void clear()
    {
        if (m_data) {
            free(m_data);
            m_data = nullptr;
            m_size = 0;
            m_capacity = 0;
        }
    }

    void grow_capacity(size_t needed_capacity)
    {
        if (m_capacity >= needed_capacity)
            return;

        ensure_capacity(needed_capacity);
    }

    void ensure_capacity(size_t needed_capacity)
    {
        if (m_capacity >= needed_capacity)
            return;

        size_t new_capacity = needed_capacity;
        auto* new_data = (T*)malloc(new_capacity * sizeof(T));

        // Move items to new location
        for (size_t i = 0; i < m_size; ++i) {
            new (&new_data[i]) T(move(at(i)));
            at(i).~T();
        }

        if (m_data)
            free(m_data);

        m_data = new_data;
        m_capacity = new_capacity;
    }

    using Iterator = VecIterator<Vec, T>;
    Iterator begin() { return Iterator(*this, 0); }
    Iterator end() { return Iterator(*this, size()); }

private:
    T* slot(size_t i) { return &data()[i]; }
    const T* slot(size_t i) const { return &data()[i]; }

private:
    size_t m_size { 0 };
    size_t m_capacity { 0 };
    T* m_data { nullptr };
};

} // namespace SD

using SD::Vec;
