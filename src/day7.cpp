#include <aoc/Challenge.h>
#include <sd/String.h>
#include <sd/Vec.h>
#include <sd/HashMap.h>

void parse_line(String &line, char separator, Vec<int> &into)
{
    Vec<String> split = line.split(separator);
    for (auto &num : split) {
        auto maybe_int = num.trim_whitespace().to_int();
        if (maybe_int.has_value())
            into.append(maybe_int.value());
    }
}

int part_one(String &buf)
{
    Vec<int> crab_positions;
    parse_line(buf, ',', crab_positions);

    auto calculate_fuel = [&](int starting) -> int {
        int sum { 0 };
        for (auto& position : crab_positions) {
            sum += abs(position - starting);
        }
        return sum;
    };

    HashMap<int, int> fuel;
    int smallest { 0 };
    for (auto& position : crab_positions) {
        if (!fuel.get(position)) {
            int total = calculate_fuel(position);
            if (smallest == 0 || total < smallest)
                smallest = total;
            fuel.insert(position, total);
        }
    }

    printf("%d\n", smallest);
    return 0;
}

int part_two(String &buf)
{
    Vec<int> crab_positions;
    parse_line(buf, ',', crab_positions);

    auto calculate_fuel = [&](int starting) -> int {
        int sum { 0 };
        for (auto& position : crab_positions) {
            int difference = abs(position - starting);
            sum += ((difference * difference) + difference) / 2;
        }
        return sum;
    };

    HashMap<int, int> fuel;
    int smallest { 0 };
    for (auto& position : crab_positions) {
        if (!fuel.get(position)) {
            int total = calculate_fuel(position);
            if (smallest == 0 || total < smallest)
                smallest = total;
            fuel.insert(position, total);
        }
    }

    printf("%d\n", smallest);
    return 0;
}

// part-one: 337488
// part-two: 89647695
int main(int argc, char *argv[])
{
    Challenge challenge { "/home/spence/code/aoc/data/day7.txt", part_one, part_two };
    return challenge.run(argc, argv);
}
