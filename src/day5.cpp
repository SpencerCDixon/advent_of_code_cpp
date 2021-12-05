#include <aoc/Challenge.h>
#include <sd/HashMap.h>
#include <sd/String.h>
#include <sd/Vec.h>

#include <unordered_map>
#include <functional>

struct Point {
    int x { 0 };
    int y { 0 };

    Point() = default;
    Point(int x, int y)
        : x(x)
        , y(y)
    {
    }
    ~Point() = default;

    Point operator+(Point const &other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Point &operator+=(Point const &other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }
    bool operator==(Point const &other) const
    {
        return x == other.x && y == other.y;
    }
    bool operator!=(Point const &other) const
    {
        return !(*this == other);
    }
    void print()
    {
        printf("point (%d,%d)\n", x, y);
    }
};

namespace std {
    template <>
    struct hash<Point>
    {
        std::size_t operator()(const Point& k) const
        {
            using std::size_t;
            using std::hash;

            return ((hash<int>()(k.x) ^ (hash<int>()(k.y) << 1)) >> 1);
        }
    };

}

template<>
struct HashKeyTrait<Point> {
    static size_t hash(const Point &value) { return value.x * 31 + value.y * 31; }
    static bool equals(const Point &lhs, const Point &rhs) { return lhs == rhs; }
};

class Line {
public:
    // TODO: Line iterator?
    Line(Point start, Point end)
        : m_start(start)
        , m_end(end)
    {
    }
    ~Line() = default;

    void for_each_point(std::function<void(Point)> fn)
    {
        Point tmp = m_start;
        Point step;
        if (is_horizontal()) {
            step = Point(m_start.x > m_end.x ? -1 : 1, 0);
        } else if (is_vertical()) {
            step = Point(0, m_start.y > m_end.y ? -1 : 1);
        } else {
            int x = (m_end.x - m_start.x) > 0 ? 1 : -1;
            int y = (m_end.y - m_start.y) > 0 ? 1 : -1;
            step = Point(x, y);
        }

        Point finish = m_end + step;

        while (tmp != finish) {
            fn(tmp);
            tmp += step;
        }
    }

    void print() const
    {
        printf("line segment (%d,%d) ---> (%d, %d)", m_start.x, m_start.y, m_end.x, m_end.y);
    }

    [[nodiscard]] bool is_vertical() const { return m_start.x == m_end.x; }
    [[nodiscard]] bool is_horizontal() const { return m_start.y == m_end.y; }

private:
    Point m_start;
    Point m_end;
};

Line parse_line(String &str_line)
{
    auto parts = str_line.split(' ');
    ASSERT(parts.size() == 3);
    auto start_parts = parts[0].split(',');
    auto end_parts = parts[2].split(',');
    ASSERT(start_parts.size() == 2 && end_parts.size() == 2);

    // FIXME: error handling
    Point start;
    start.x = start_parts[0].to_int().value();
    start.y = start_parts[1].to_int().value();

    Point end;
    end.x = end_parts[0].to_int().value();
    end.y = end_parts[1].to_int().value();
    return { start, end };
}

int part_one(String &buf)
{
    Vec<String> lines = buf.split('\n');
    Vec<Line> valid_line_segments;
    for (auto &line : lines) {
        auto line_segment = parse_line(line);
        if (line_segment.is_horizontal() || line_segment.is_vertical()) {
            valid_line_segments.append(line_segment);
        }
    }

    std::unordered_map<Point, int> point_counts;
    for (auto &line_segment : valid_line_segments) {
        line_segment.for_each_point([&](auto point) {
            if (!point_counts.contains(point))
                point_counts[point] = 1;
            else
                point_counts[point]++;
        });
    }

    int total { 0 };
    for (auto &el : point_counts)
    {
        if (el.second >= 2)
            total++;
    }

    return total;
}

int part_two(String &buf)
{
    Vec<String> lines = buf.split('\n');
    Vec<Line> valid_line_segments;
    for (auto &line : lines) {
        valid_line_segments.append(parse_line(line));
    }

    std::unordered_map<Point, int> point_counts;
    for (auto &line_segment : valid_line_segments) {
        line_segment.for_each_point([&](auto point) {
            if (!point_counts.contains(point))
                point_counts[point] = 1;
            else
                point_counts[point]++;
        });
    }

    int total { 0 };
    for (auto &el : point_counts)
    {
        if (el.second >= 2)
            total++;
    }

    return total;
}

// part-one: 7085
// part-two: 20271
int main(int argc, char *argv[])
{
    Challenge challenge { "/home/spence/code/aoc/data/day5.txt", part_one, part_two };
    auto result = challenge.run(argc, argv);
    printf("%d", result);
    return 0;
}
