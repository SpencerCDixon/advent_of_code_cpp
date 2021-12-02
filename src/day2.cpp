#include <cassert>
#include <cstdio> // fopen
#include <cstdlib>
#include <cstring>
#include <sys/stat.h> // fstat

#include <sd/Vec.h>
#include <sd/String.h>

class ElvishSubmarine {
public:
    ElvishSubmarine() = default;
    ~ElvishSubmarine() = default;

    void forward(int amount) { m_horizontal += amount; }
    void up(int amount) { m_depth -= amount; }
    void down(int amount) { m_depth += amount; }

    [[nodiscard]] int total() const { return m_horizontal * m_depth; }
private:
    int m_horizontal { 0 };
    int m_depth { 0 };
};

int part_one(char *buf)
{
    ElvishSubmarine sub;
    Vec<String> lines = String(buf).split('\n');

    for (auto& line : lines) {
        auto split = line.split(' ');
        if (split.size() != 2)
            continue;

        if (split[0] == String("forward")) {
            auto value = split[1].to_int();
            sub.forward(value.value_or(0));
        } else if (split[0] == String("down")) {
            auto value = split[1].to_int();
            sub.down(value.value_or(0));
        } else if (split[0] == String("up")) {
            auto value = split[1].to_int();
            sub.up(value.value_or(0));
        }
    }
    return sub.total();
}

int part_two(char *buf)
{
    return 0;
}

// part-one: 2091984
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

    FILE *fd = fopen("/home/spence/code/aoc/data/day2.txt", "r");
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
