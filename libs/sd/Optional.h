#pragma once

#include "Types.h"
#include "Utility.h"
#include <cstdio>
#include <new>

namespace SD {

template<typename T>
class Optional {
public:
    Optional() = default;
    Optional(T const &value)
        : m_none(false)
    {
        new (&m_storage) T(value);
    }
    Optional(T &&value) : m_none(false)
    {
        new (&m_storage) T(move(value));
    }
    Optional(Optional&& other) : m_none(other.m_none) {
        if (has_value()) {
            new (&m_storage) T(other.release_value());
        }
    }

    ~Optional()
    {
        if (has_value()) {
            (*reinterpret_cast<T *>(&m_storage)).~T();
        }
    }

    T &value() &
    {
        ASSERT(!m_none);
        return *reinterpret_cast<T *>(&m_storage);
    }

    const T &value() const&
    {
        ASSERT(!m_none);
        return *reinterpret_cast<const T *>(&m_storage);
    }

    T release_value()
    {
        ASSERT(!m_none); // We can only release if we have a value
        T tmp = move(value());
        value().~T();
        m_none = true;
        return tmp;
    }

    [[nodiscard]] bool is_none() { return m_none; }
    [[nodiscard]] bool is_none() const { return m_none; }
    [[nodiscard]] bool has_value() { return !m_none; }
    [[nodiscard]] bool has_value() const { return !m_none; }

private:
    alignas(T) u8 m_storage[sizeof(T)] { 0 };
    bool m_none { true };
};

} // namespace SD

using SD::Optional;