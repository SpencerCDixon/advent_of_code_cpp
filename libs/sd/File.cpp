#include "File.h"

#include <cstdio>     // fopen
#include <sys/stat.h> // fstat

Result<Ref<File>, Error> File::open(const String &path, File::OpenOptions options)
{
    Ref<File> file = Ref<File>::make(File(path));
    auto error = file->open(options);
    if (error.has_value()) {
        return { error.value() };
    }
    return { file };
}

String File::read_all()
{
    ASSERT(m_handle);
    size_t bytes = size();
    char *buf = (char *)malloc(bytes);
    auto read = fread(buf, 1, bytes, m_handle);
    ASSERT(read == bytes);
    String result { buf };
    free(buf);
    return result;
}

size_t File::size() const
{
    ASSERT(m_handle);

    struct stat st;
    int rc = fstat(fileno(m_handle), &st);
    if (rc < 0) {
        return 0;
    }

    return st.st_size;
}

Optional<Error> File::open(File::OpenOptions options)
{
    ASSERT(options);

    String open_mode;
    if (options & OpenOptions::Read)
        open_mode += "r";
    if (options & OpenOptions::Write)
        open_mode += "w";

    m_handle = fopen(m_path.characters(), open_mode.characters());
    if (!m_handle)
        return { Error::from_errno(errno) };

    return {};
}
