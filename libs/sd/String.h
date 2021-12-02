#pragma once

#include "Utility.h"
#include "Vec.h"
#include "Optional.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

// TODO:
// * swap
// * better operator+/-

class String {
public:
    String()
    {
        set_string("");
    }

    String(const char* c_string)
    {
        set_string(c_string);
    }

    String(const String& other)
    {
        set_string(other.m_characters);
    }

    String(String&& other)
    {
        m_characters = other.m_characters;
        m_length = other.m_length;

        other.m_length = 0;
        other.m_characters = nullptr;
    }
    String(const char* c_string, size_t length)
    {
        m_length = length;
        delete[] m_characters;
        m_characters = new char[m_length + 1];
        memcpy(m_characters, c_string, length);
        m_characters[length] = '\0';
    }

    String& operator=(const String& other)
    {
        // FIXME: Self assignment
        set_string(other.m_characters);
        return *this;
    }

    ~String()
    {
        delete[] m_characters;
    }

    [[nodiscard]] const char* characters() const { return m_characters; }
    [[nodiscard]] char* characters() { return m_characters; }
    [[nodiscard]] size_t length() const { return m_length; }

    String& operator+=(const String& other)
    {
        char* new_characters = new char[m_length + other.m_length + 1];
        new_characters[0] = '\0';
        strcat(new_characters, m_characters);
        strcat(new_characters, other.m_characters);
        delete[] m_characters;
        m_characters = new_characters;
        m_length += other.m_length + 1;
        return *this;
    }

    enum class TrimLocation {
        Left,
        Right,
        Both
    };
    String trim_whitespace(TrimLocation location = TrimLocation::Both);
    String substring(size_t start, size_t length);
    Vec<String> split(char separator);

    Optional<int> to_int();

private:
    void set_string(const char* c_string)
    {
        delete[] m_characters;
        m_length = strlen(c_string);
        m_characters = new char[m_length + 1];
        strcpy(m_characters, c_string);
    }

private:
    char* m_characters { nullptr };
    size_t m_length { 0 };
};

String operator+(const String&, const String&);
String operator+(const String&, const char*);

bool operator==(const String&, const String&);
bool operator!=(const String&, const String&);
