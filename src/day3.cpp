#include <cassert>
#include <cstdio> // fopen
#include <cstdlib>
#include <cstring>
#include <sys/stat.h> // fstat

#include <sd/String.h>
#include <sd/Vec.h>

int part_one(char *buf)
{
    Vec<String> lines = String(buf).split('\n');
    ASSERT(!lines.is_empty());

    size_t column_count = lines.size() / 2;
    Vec<size_t> counts = Vec<size_t>::with_capacity(lines[0].length(), 0);

    for (auto &line : lines) {
        for (size_t i = 0; i < line.length(); ++i) {
            if (line.characters()[i] == '1') {
                counts[i]++;
            }
        }
    }

    u16 gamma { 0 };
    u16 epsilon { 0 };
    for (size_t i = 0; i < counts.size(); ++i) {
        gamma |= (counts[i] > column_count ? 1 : 0) << (counts.size() - i - 1);
        epsilon |= (counts[i] > column_count ? 0 : 1) << (counts.size() - i - 1);
    }

    printf("\ngamma: %d\n", gamma);
    printf("epsilon: %d\n", epsilon);
    return gamma * epsilon;
}

int part_two(char *buf)
{
    return 0;
}

// part-one: 3633500
// part-two: 0
int main(int argc, char *argv[])
{
    bool should_run_part_two = false;
    if (argc > 1) {
        for (int i = 0; i < argc; ++i) {
            char *arg = argv[i];
            if (strcmp(arg, "part-two") == 0) {
                should_run_part_two = true;
                break;
            }
        }
    }

    FILE *fd = fopen("/home/spence/code/aoc/data/day3.txt", "r");
    if (!fd) {
        perror("fopen");
        return 1;
    }

    struct stat st;
    int rc = fstat(fileno(fd), &st);
    if (rc < 0) {
        perror("fstat");
        return 1;
    }

    char *buf = static_cast<char *>(malloc(st.st_size));
    rc = fread(buf, 1, st.st_size, fd);
    ASSERT(rc == st.st_size);

    int result = should_run_part_two ? part_two(buf) : part_one(buf);
    printf("%d", result);
    return 0;
}
