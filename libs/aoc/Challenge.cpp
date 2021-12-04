//
// Created by Spencer Dixon on 12/3/21.
//

#include "Challenge.h"

#include <sd/File.h>

Challenge::Challenge(const char *input_data, PartHandler part_one, PartHandler part_two)
    : m_input_data_path(String(input_data))
    , m_part_one(part_one)
    , m_part_two(part_two)
{
    // FIXME: Possible enhancements:
    //   * derive input path based on ENV variable/day number
    //   * allow for fetching of input data remotely and cache locally
    //   * nicer argument parsing for specifying which daily part to run
}

int Challenge::run(int argc, char **argv)
{
    bool should_run_part_two = false;
    if (argc > 1) {
        for (int i = 0; i < argc; ++i) {
            char *arg = argv[i];
            if (String(arg) == "part-two")) {
                should_run_part_two = true;
                break;
            }
        }
    }

    auto file = File::open(m_input_data_path, File::OpenOptions::Read);
    if (file.is_error()) {
        fprintf(stderr, "error opening input data: %s\n", file.error().message());
        return -1;
    }

    auto buf = file.value()->read_all();
    return should_run_part_two ? m_part_two(buf) : m_part_one(buf);
}
