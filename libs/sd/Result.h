#pragma once

#include "Optional.h"
#include "Ref.h"

#include <cerrno>
#include <cstdlib>
#include <cstring>

namespace SD {

class Error {
public:
    static Error from_errno(int code) { return { code }; }

    [[nodiscard]] const char *message() const {
        static const char* unknown_message = "Unknown error type";
        if (m_errno_code != 0) {
            return strerror(m_errno_code);
        }

        return unknown_message;
    }

protected:
    Error(int code) : m_errno_code(code) {}

private:
    int m_errno_code { 0 };
};

template<typename ValueType, typename ErrorType>
class Result {
public:
    Result(ValueType const &v)
        : m_value(v)
    {
    }
    Result(ValueType &&v)
        : m_value(move(v))
    {
    }
    Result(ErrorType const &e)
        : m_error(e)
    {
    }
    Result(ErrorType &&e)
        : m_error(move(e))
    {
    }

    [[nodiscard]] bool is_error() const { return m_error.has_value(); }
    [[nodiscard]] bool is_ok() const { return m_value.has_value(); }

    ValueType &value() { return m_value.value(); }
    ErrorType &error() { return m_error.value(); }

private:
    Optional<ValueType> m_value;
    Optional<ErrorType> m_error;
};

} // namespace SD

using SD::Error;
using SD::Result;
