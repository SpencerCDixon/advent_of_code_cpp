#include <aoc/Challenge.h>
#include <sd/File.h>
#include <sd/String.h>
#include <sd/Vec.h>

int part_one(String &buf)
{
    Vec<String> lines = buf.split('\n');
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

    return gamma * epsilon;
}

String find_rating(Vec<String> lines, size_t index, bool use_most_common_bit)
{
    ASSERT(!lines.is_empty());
    if (lines.size() == 1)
        return lines.first();

    Vec<size_t> counts = Vec<size_t>::with_capacity(lines[0].length(), 0);
    for (auto &line : lines) {
        for (size_t i = 0; i < line.length(); ++i) {
            if (line.characters()[i] == '1') {
                counts[i]++;
            }
        }
    }

    Vec<String> next;
    bool has_more_ones = counts[index] >= (lines.size() / 2);

    for (auto &line : lines) {
        if (has_more_ones && line.characters()[index] == (use_most_common_bit ? '1' : '0')) {
            next.append(line);
        } else if (!has_more_ones && line.characters()[index] == (use_most_common_bit ? '0' : '1')) {
            next.append(line);
        }
    }

    return find_rating(next, ++index, use_most_common_bit);
}

int part_two(String &buf)
{
    Vec<String> lines = buf.split('\n');
    auto oxygen = find_rating(lines, 0, true);
    auto c02_scrubber = find_rating(lines, 0, false);
    return oxygen.to_int(2).value() * c02_scrubber.to_int(2).value();
}

// part-one: 3633500
// part-two: 4550283
int main(int argc, char *argv[])
{
    Challenge challenge { "/home/spence/code/aoc/data/day3.txt", part_one, part_two };
    auto result = challenge.run(argc, argv);
    printf("%d", result);
    return 0;
}
