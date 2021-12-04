#pragma once

#include "Ref.h"
#include "Result.h"
#include "String.h"

class File {
public:
    enum OpenOptions {
        Read = BIT(0),
        Write = BIT(1),
    };

    static Result<Ref<File>, Error> open(String const &path, OpenOptions options = OpenOptions::Read);
    // TODO: create?

    File() = default;
    ~File()
    {
        if (m_handle)
            fclose(m_handle);
    }

    File &operator=(const File &other)
    {
        File tmp(other);
        swap_self(tmp);
        return *this;
    }

    String read_all();

    [[nodiscard]] size_t size() const;
    [[nodiscard]] bool empty() const { return size() == 0; }

private:
    explicit File(String path)
        : m_path(move(path))
    {
    }

    void swap_self(File &other)
    {
        String path = m_path;
        FILE *handle = m_handle;
        m_path = other.m_path;
        m_handle = other.m_handle;
        other.m_handle = handle;
        other.m_path = path;
    }

    Optional<Error> open(OpenOptions = OpenOptions::Read);

private:
    String m_path;
    FILE *m_handle { nullptr };
};