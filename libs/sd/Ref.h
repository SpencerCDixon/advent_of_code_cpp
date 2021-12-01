#pragma once

#include <cstddef>

#include "Utility.h"

namespace SD {

// NOTE: Ref is not currently thread safe. Adding/removing references is not yet atomic.
template<typename T>
class Ref {
public:
    // TODO: Forward args to T
    static Ref make(T data)
    {
        auto *control_block = new ControlBlock;
        control_block->data = data;

        Ref ref;
        ref.m_control_block = control_block;
        return ref;
    }

    Ref() = default;

    ~Ref()
    {
        clear();
    }

    Ref(Ref &&other) noexcept
    {
        m_control_block = exchange(other.m_control_block, nullptr);
    }

    Ref(Ref const &other)
    {
        if (!other.empty()) {
            m_control_block = other.m_control_block;
            m_control_block->count++;
        }
    }
    Ref(std::nullptr_t)
    {
    }

    Ref &operator=(Ref const &other)
    {
        Ref tmp(other);
        swap_self(tmp);
        return *this;
    }

    Ref &operator=(Ref &&other) noexcept
    {
        Ref tmp(move(other));
        swap_self(tmp);
        return *this;
    }

    T *operator->()
    {
        return get();
    }
    T const &operator*() const
    {
        ASSERT(m_control_block);
        return m_control_block->data;
    };
    T &operator*()
    {
        ASSERT(m_control_block);
        return m_control_block->data;
    };

    T *get()
    {
        if (m_control_block)
            return &m_control_block->data;
        return nullptr;
    }

    [[nodiscard]] bool empty() const
    {
        return m_control_block == nullptr;
    }

    void clear()
    {
        if (!m_control_block)
            return;

        m_control_block->count -= 1;

        if (m_control_block->count == 0) {
            delete m_control_block;
        }
    }

private:
    void swap_self(Ref &other)
    {
        ControlBlock *tmp = m_control_block;
        m_control_block = other.m_control_block;
        other.m_control_block = tmp;
    }

    // ControlBlock owns the underlying content being shared between the refs.
    struct ControlBlock {
        size_t count { 1 };
        T data;
    };

    ControlBlock *m_control_block { nullptr };
};

} // namespace SD

using SD::Ref;
