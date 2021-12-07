#pragma once

#include "Ref.h"
#include "Result.h"
#include "String.h"
#include "Utility.h"

// TODO:
// * File::create()
// * read_into(buf)

class File {
    SD_MAKE_NONCOPYABLE(File)
public:
    enum OpenOptions {
        Read = BIT(0),
        Write = BIT(1),
    };

    static Result<Ref<File>, Error> open(String const &path, OpenOptions options = OpenOptions::Read);

    explicit File(String path)
        : m_path(move(path))
    {
    }

    File() = default;
    ~File()
    {
        if (m_handle)
            fclose(m_handle);
    }

    String read_all();
    Vec<String> read_lines();

    [[nodiscard]] size_t size() const;
    [[nodiscard]] bool empty() const { return size() == 0; }

private:
    Optional<Error> open(OpenOptions = OpenOptions::Read);

private:
    String m_path;
    FILE *m_handle { nullptr };
};