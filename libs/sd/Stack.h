#pragma once

#include "Vec.h"

template<typename Value>
class Stack {
public:
    Stack() = default;
    ~Stack() = default;

    [[nodiscard]] bool is_empty() const { return m_storage.is_empty(); }

    void push(Value v)
    {
        m_storage.append(move(v));
    }

    Value pop()
    {
        Value result = m_storage.last();
        m_storage.pop_last();
        return result;
    }

    size_t size() const
    {
        return m_storage.size();
    }

private:
    Vec<Value> m_storage;
};