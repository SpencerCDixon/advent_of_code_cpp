#include <assert.h>
#include <stdio.h> // fopen
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // fstat

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
    // TODO: create a Vec<int>
    return 0;
}

// part-one: 1655
// part-two: XXXX
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

    int num_increased { 0 };
    if (should_run_part_two) {
        num_increased = part_two(buf);
    } else {
        num_increased = part_one(buf);
    }

    printf("%d", num_increased);
    return 0;
}
