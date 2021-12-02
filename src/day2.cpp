#include <cassert>
#include <cstdio> // fopen
#include <cstdlib>
#include <cstring>
#include <sys/stat.h> // fstat

#include <sd/String.h>
#include <sd/Vec.h>

class Submarine {
public:
    virtual void forward(int amount) = 0;
    virtual void up(int amount) = 0;
    virtual void down(int amount) = 0;
    [[nodiscard]] virtual int calculate_position() const = 0;

    void execute_commands(Vec<String> &commands)
    {
        for (auto &command : commands) {
            auto split = command.split(' ');
            if (split.size() != 2)
                continue;

            if (split[0] == String("forward")) {
                forward(split[1].to_int().value_or(0));
            } else if (split[0] == String("down")) {
                down(split[1].to_int().value_or(0));
            } else if (split[0] == String("up")) {
                up(split[1].to_int().value_or(0));
            }
        }
    }
};

class BrokenElvishSubmarine : public Submarine {
public:
    BrokenElvishSubmarine() = default;
    ~BrokenElvishSubmarine() = default;

    void forward(int amount) override { m_horizontal += amount; }
    void up(int amount) override { m_depth -= amount; }
    void down(int amount) override { m_depth += amount; }
    [[nodiscard]] int calculate_position() const override { return m_horizontal * m_depth; }

private:
    int m_horizontal { 0 };
    int m_depth { 0 };
};

//class ElvishSubmarine {
//public:
//    ElvishSubmarine() = default;
//    ~ElvishSubmarine() = default;
//
//    void forward(int amount) { m_horizontal += amount; }
//    void up(int amount) { m_depth -= amount; }
//    void down(int amount) { m_depth += amount; }
//
//    [[nodiscard]] int total() const { return m_horizontal * m_depth; }
//
//private:
//    int m_aim { 0 };
//    int m_horizontal { 0 };
//    int m_depth { 0 };
//};

int part_one(char *buf)
{
    BrokenElvishSubmarine sub;
    Vec<String> commands = String(buf).split('\n');
    sub.execute_commands(commands);
    return sub.calculate_position();
}

int part_two(char *buf)
{
    //    ElvishSubmarine sub;
    //    Vec<String> lines = String(buf).split('\n');
    //    return sub.calculate_position();
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
