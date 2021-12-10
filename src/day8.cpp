#include <aoc/Challenge.h>
#include <sd/HashMap.h>
#include <sd/String.h>
#include <sd/Vec.h>

int part_one(String &buf)
{
    Vec<String> lines = buf.split('\n');

    int unique_signals { 0 };
    for (auto& line : lines) {
        auto split = line.split('|');
        if (split.size() != 2)
            continue;

        auto output = split[1];

        auto is_unique_signal = [](size_t size) {
            return size == 2 || size == 3 || size == 4 || size == 7;
        };

        Vec<String> output_signals = output.split(' ');
        for (auto &signal : output_signals) {
            if (is_unique_signal(signal.length()))
                unique_signals++;
        }
    }

    printf("%d\n", unique_signals);
    return 0;
}
int part_two(String &buf)
{
    return 0;
}

// part-one: 0
// part-two: 0
int main(int argc, char *argv[])
{
    Challenge challenge { "/home/spence/code/aoc/data/day8.txt", part_one, part_two };
    return challenge.run(argc, argv);
}
