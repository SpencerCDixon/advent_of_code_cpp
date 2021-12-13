#include <aoc/Challenge.h>
#include <sd/String.h>
#include <sd/Utility.h>
#include <sd/Vec.h>

#include <cstdlib>
#include <functional>

struct Point {
    int x;
    int y;
};

template<typename GridValue>
class Grid {
public:
    Grid(Vec<GridValue> storage, int width, int height)
        : m_storage(move(storage))
        , m_width(width)
        , m_height(height) {};
    ~Grid() = default;

    GridValue &at(int x, int y)
    {
        ASSERT(x < m_width && y < m_height);
        return m_storage[(y * m_width + x)];
    }

    void for_each_ordered(std::function<void(GridValue &, int x, int y)> fn)
    {
        for (int y = 0; y < m_height; ++y) {
            for (int x = 0; x < m_width; ++x) {
                fn(at(x, y), x, y);
            }
        }
    }

    Vec<GridValue> surrounding_values(int x, int y)
    {
        Vec<GridValue> result;
        for (auto p : surrounding_points({ x, y })) {
            result.append(at(p.x, p.y));
        }
        return result;
    }

    Vec<Point> surrounding_points(Point p)
    {
        Vec<Point> result;

        if (p.x % m_width)
            result.append({ p.x - 1, p.y });
        if (p.x < (m_width - 1))
            result.append({ p.x + 1, p.y });
        if (p.y % m_height)
            result.append({ p.x, p.y - 1 });
        if (p.y < (m_height - 1))
            result.append({ p.x, p.y + 1 });

        return result;
    }

private:
    Vec<GridValue> m_storage;
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
        int val = strtol(tmp, nullptr, 10);
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
    Grid<int> grid(grid_data, grid_width, grid_height);

    int total { 0 };
    grid.for_each_ordered([&](auto value, int x, int y) {
        bool is_lowest { true };
        for (auto nearby : grid.surrounding_values(x, y)) {
            if (nearby <= value) {
                is_lowest = false;
                break;
            }
        }

        if (is_lowest)
            total += (value + 1);
    });

    printf("%d\n", total);
    return 0;
}

struct Tile {
    bool been_visited { false };
    bool is_wall { false };
    int value { -1 };
};

void flood_fill_at(Grid<Tile> &grid, Point start, int *num_tiles_touched)
{
    auto &tile = grid.at(start.x, start.y);
    if (tile.is_wall || tile.been_visited) {
        return;
    }

    if (!tile.been_visited) {
        tile.been_visited = true;
        (*num_tiles_touched)++;
    }

    for (auto point : grid.surrounding_points(start)) {
        flood_fill_at(grid, point, num_tiles_touched);
    }
}

int compare_ints(const void *elem1, const void *elem2)
{
    int f = *((int *)elem1);
    int s = *((int *)elem2);
    if (f > s)
        return -1;
    if (f < s)
        return 1;
    return 0;
}

int part_two(String &buf)
{
    Vec<String> lines = buf.split('\n');

    int grid_width { 100 };
    int grid_height { 100 };

    Vec<int> grid_data;
    Vec<Tile> flood_data;
    flood_data.grow_capacity(grid_width * grid_height);
    grid_data.grow_capacity(grid_width * grid_height);

    for (auto &line : lines) {
        parse_line(line, grid_data);
    }

    for (auto value : grid_data) {
        flood_data.append({ .been_visited = false, .is_wall = (value == 9), .value = value });
    }

    ASSERT((int)grid_data.size() == grid_width * grid_height);
    Grid<int> grid(grid_data, grid_width, grid_height);
    Grid<Tile> flood(flood_data, grid_width, grid_height);

    Vec<Point> low_points;
    grid.for_each_ordered([&](auto value, int x, int y) {
        bool is_lowest { true };
        for (auto nearby : grid.surrounding_values(x, y)) {
            if (nearby <= value) {
                is_lowest = false;
                break;
            }
        }

        if (is_lowest)
            low_points.append({ x, y });
    });

    Vec<int> basin_sizes;
    for (auto point : low_points) {
        int basin_size { 0 };
        flood_fill_at(flood, point, &basin_size);
        basin_sizes.append(basin_size);
    }

    qsort(basin_sizes.data(), basin_sizes.size(), sizeof(int), compare_ints);

    int result = basin_sizes.first() * basin_sizes.second() * basin_sizes.third();
    printf("%d\n", result);
    return 0;
}

// part-one: 425
// part-two: 1135260
int main(int argc, char *argv[])
{
    Challenge challenge { "/home/spence/code/aoc/data/day9.txt", part_one, part_two };
    return challenge.run(argc, argv);
}
