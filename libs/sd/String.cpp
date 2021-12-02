#include "String.h"

#include <stdlib.h>
#include <string.h>

String operator+(const String& lhs, const String& rhs)
{
    String tmp = lhs;
    tmp += rhs;
    return tmp;
}

String operator+(const String& lhs, const char* rhs)
{
    String tmp = lhs;
    tmp += rhs;
    return tmp;
}

bool operator==(const String& lhs, const String& rhs)
{
    return strcmp(lhs.characters(), rhs.characters()) == 0;
}

bool operator!=(const String& lhs, const String& rhs)
{
    return strcmp(lhs.characters(), rhs.characters()) != 0;
}

String String::trim_whitespace(TrimLocation location)
{
    auto is_whitespace_character = [](char ch) -> bool {
        return ch == '\t'
            || ch == '\n'
            || ch == '\v'
            || ch == '\f'
            || ch == '\r'
            || ch == ' ';
    };

    size_t substring_start = 0;
    size_t substring_length = length();

    if (location == TrimLocation::Both || location == TrimLocation::Right) {
        for (size_t i = length() - 1; i > 0; --i) {
            if (substring_length == 0)
                return "";
            if (!is_whitespace_character(characters()[i]))
                break;
            --substring_length;
        }
    }

    if (location == TrimLocation::Both || location == TrimLocation::Left) {
        for (size_t i = 0; i < length(); ++i) {
            if (substring_length == 0)
                return "";
            if (!is_whitespace_character(characters()[i]))
                break;
            ++substring_start;
            --substring_length;
        }
    }

    return substring(substring_start, substring_length);
}

Vec<String> String::split(char separator)
{
    if (!length())
        return {};

    Vec<String> result {};

    size_t last_start = 0;
    for (size_t i = 0; i < length(); ++i) {
        char ch = characters()[i];

        if (ch == separator) {
            size_t sub_length = i - last_start;
            if (sub_length != 0)
                result.append(substring(last_start, sub_length));
            last_start = i + 1;
        }
    }

    size_t tail_length = length() - last_start;
    if (tail_length != 0)
        result.append(substring(last_start, tail_length));

    return result;
}

String String::substring(size_t start, size_t length)
{
    if (!length)
        return {};

    ASSERT(start + length <= this->length());
    return { characters() + start, length };
}

Optional<int> String::to_int()
{
    if (*this == "0")
        return { 0 };

    int val = atoi(characters());

    if (!val)
        return {};

    return { val };
}
