#include <aoc/Challenge.h>
#include <sd/String.h>
#include <sd/Utility.h>
#include <sd/Vec.h>

class Grid {
public:
    Grid(Vec<int> storage, int width, int height)
        : m_storage(move(storage)), m_width(width), m_height(height) {};
    ~Grid() = default;

    int at(int x, int y)
    {
        ASSERT(x < m_width && y < m_height);
        return m_storage[(y * m_width + x)];
    }

    Vec<int> surrounding(int x, int y)
    {
        Vec<int> result;

        if (x % m_width) {
            result.append(at(x - 1, y));
        }
        if (x < (m_width - 1)) {
            result.append(at(x + 1, y));
        }
        if (y % m_height) {
            result.append(at(x, y - 1));
        }
        if (y < (m_height - 1)) {
            result.append(at(x, y + 1));
        }

        return result;
    }

private:
    int m_height;
    int m_width;
    Vec<int> m_storage;
};

Vec<int> parse_line(String &line)
{
    Vec<int> result;
    for (size_t i = 0; i < line.length(); ++i) {
        auto value = line.substring(i, 1).to_int(); // FIXME: Gross, get [] or at() subscripting soon
        if (value.has_value())
            result.append(value.value());
    }

    return result;
}

// 1 - low points are lower in all four quadrants
// 2 - risk level is the low pointer number + 1
// 3 - total is the sum of all low points with risk added in
int part_one(String &buf)
{
    auto result = parse_line(buf);
    Grid grid(result, 100, 100);

    int total { 0 };
    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 5; ++y) {
            bool is_lowest { true };
            auto location = grid.at(x, y);
            for (auto nearby : grid.surrounding(x, y)) {
                if (nearby < location) {
                    is_lowest = false;
                    break;
                }
            }

            if (is_lowest) {
                total += (location + 1);
            }

        }
    }

//    printf("%d\n", total);
    printf("0\n");

    return 0;
}
int part_two(String &buf)
{
    printf("0\n");

    return 0;
}

// part-one: 0
// part-two: 0
int main(int argc, char *argv[])
{
    Challenge challenge { "/home/spence/code/aoc/data/day9.txt", part_one, part_two };
    return challenge.run(argc, argv);
}
