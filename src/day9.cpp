#include <aoc/Challenge.h>
#include <sd/String.h>
#include <sd/Utility.h>
#include <sd/Vec.h>

#include <cstdlib>

class Grid {
public:
    Grid(Vec<int> storage, int width, int height)
        : m_storage(move(storage))
        , m_width(width)
        , m_height(height) {};
    ~Grid() = default;

    int at(int x, int y)
    {
        ASSERT(x < m_width && y < m_height);
        return m_storage[(y * m_width + x)];
    }

    Vec<int> surrounding(int x, int y)
    {
        Vec<int> result;

        if (x % m_width) result.append(at(x - 1, y));
        if (x < (m_width - 1)) result.append(at(x + 1, y));
        if (y % m_height) result.append(at(x, y - 1));
        if (y < (m_height - 1)) result.append(at(x, y + 1));

        return result;
    }

private:
    Vec<int> m_storage;
    int m_width;
    int m_height;
};

void parse_line(String &line, Vec<int> &into)
{
    for (size_t i = 0; i < line.length(); ++i) {
        if (line.characters()[i] == '\n')
            continue;

        char tmp[2] = {
            line.characters()[i],
            '\0',
        };
        int val = strtol(tmp, NULL, 10);
        ASSERT(val >= 0);
        into.append(val);
    }
}

int part_one(String &buf)
{
    Vec<String> lines = buf.split('\n');

    int grid_width { 100 };
    int grid_height { 100 };

    Vec<int> grid_data;
    grid_data.grow_capacity(grid_width * grid_height);

    for (auto &line : lines) {
        parse_line(line, grid_data);
    }
    ASSERT((int)grid_data.size() == grid_width * grid_height);
    Grid grid(grid_data, grid_width, grid_height);

    int total { 0 };
    for (int y = 0; y < grid_height; ++y) {
        for (int x = 0; x < grid_width; ++x ) {
            bool is_lowest { true };
            auto location = grid.at(x, y);
            for (auto nearby : grid.surrounding(x, y)) {
                if (nearby <= location) {
                    is_lowest = false;
                    break;
                }
            }

            if (is_lowest)
                total += (location + 1);
        }
    }

    printf("%d\n", total);
    return 0;
}
int part_two(String &buf)
{
    printf("0\n");

    return 0;
}

// part-one: 425
// part-two: 0
int main(int argc, char *argv[])
{
    Challenge challenge { "/home/spence/code/aoc/data/day9.txt", part_one, part_two };
    return challenge.run(argc, argv);
}
