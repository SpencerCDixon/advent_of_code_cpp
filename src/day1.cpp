#include <assert.h>
#include <stdio.h> // fopen
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // fstat

#include <sd/Vec.h>

int part_one(char *buf)
{
    int previous_value { 0 };
    int num_increased { 0 };
    int num_decreased { 0 };

    char *line = strtok(buf, "\n");
    previous_value = atoi(line);

    while (line) {
        line = strtok(NULL, "\n");
        if (line == NULL) {
            continue;
        }

        int value = atoi(line);

        if (previous_value < value) {
            num_increased++;
        } else if (previous_value > value) {
            num_decreased++;
        }
        previous_value = value;
    }

    return num_increased;
}

int part_two(char *buf)
{
    Vec<int> values;

    auto add_value = [&](char *line) {
        if (!line)
            return;
        int value = atoi(line);
        if (value > 0) {
            values.append(value);
        }
    };

    char *line = strtok(buf, "\n");
    add_value(line);

    while (line) {
        line = strtok(NULL, "\n");
        add_value(line);
    }

    int idx { 0 };
    int num_increased { 0 };
    while (idx < (values.size() - 3)) {
        int current[3] = { values[idx], values[idx + 1], values[idx + 2] };
        int next[3] = { values[idx + 1], values[idx + 2], values[idx + 3] };

        auto sum = [&](const int* vals) -> int {
            return vals[0] + vals[1] + vals[2];
        };

        if (sum(next) > sum(current))
            num_increased++;

        idx++;
    }

    return num_increased;
}

// part-one: [1655]
// part-two: [1683]
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

    FILE *fd = fopen("/home/spence/code/aoc/data/day1.txt", "r");
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

    char buf[st.st_size];
    rc = fread(buf, 1, st.st_size, fd);
    assert(rc == st.st_size);

    int num_increased = should_run_part_two ? part_two(buf) : part_one(buf);
    printf("%d", num_increased);
    return 0;
}
