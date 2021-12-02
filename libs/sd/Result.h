#pragma once

#include "Optional.h"

namespace SD {

template<typename Value, typename Error>
class Result {
public:
    Result(Value const &v)
        : m_value(v)
    {
    }
    Result(Value &&v)
        : m_value(move(v))
    {
    }
    Result(Error const &e)
        : m_error(e)
    {
    }
    Result(Error &&e)
        : m_error(move(e))
    {
    }

    [[nodiscard]] bool is_error() const { return m_error.has_value(); }
    [[nodiscard]] bool is_ok() const { return m_value.has_value(); }

    Value& value() { return m_value.value(); }
    Error& error() { return m_error.value(); }

private:
    Optional<Value> m_value;
    Optional<Error> m_error;
};

} // namespace SD

using SD::Result;
