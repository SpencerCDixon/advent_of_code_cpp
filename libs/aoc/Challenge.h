#pragma once

#include <sd/String.h>

typedef int (*PartHandler)(String &);

class Challenge {
public:
    Challenge(const char* input_data, PartHandler part_one, PartHandler part_two);
    ~Challenge() = default;

    int run(int argc, char** argv);

private:
    String m_input_data_path;
    PartHandler m_part_one { nullptr };
    PartHandler m_part_two { nullptr };
};