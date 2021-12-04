#include <aoc/Challenge.h>
#include <sd/Vec.h>
#include <sd/String.h>

int part_one(String& buf)
{
    int num_increased { 0 };
    Vec<String> lines = buf.split('\n');

    if (lines.is_empty())
        return 0;

    int previous_value = lines[0].to_int().value();
    for (auto& line : lines) {
        auto maybe_value = line.to_int();
        if (!maybe_value.has_value())
            continue;

        if (maybe_value.value() > previous_value)
            num_increased++;

        previous_value = maybe_value.value();
    }

    return num_increased;
}

int part_two(String& buf)
{
    Vec<String> lines = buf.split('\n');
    if (lines.is_empty())
        return 0;

    Vec<int> values;
    for (auto& line : lines) {
        auto maybe_value = line.to_int();
        if (maybe_value.has_value())
            values.append(maybe_value.value());
    }

    size_t idx { 0 };
    int num_increased { 0 };
    while (idx < (values.size() - 3)) {
        int current = values[idx] + values[idx + 1] + values[idx + 2];
        int next = values[idx + 1] + values[idx + 2] + values[idx + 3];

        if (next > current)
            num_increased++;

        idx++;
    }

    return num_increased;
}

// part-one: 1655
// part-two: 1683
int main(int argc, char *argv[])
{
    Challenge challenge { "/home/spence/code/aoc/data/day1.txt", part_one, part_two };
    auto result = challenge.run(argc, argv);
    printf("%d", result);
    return 0;
}
