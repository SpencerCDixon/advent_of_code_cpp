#include <aoc/Challenge.h>
#include <sd/Vec.h>
#include <sd/String.h>

class Submarine {
public:
    Submarine() = default;
    ~Submarine() = default;

    virtual void forward(int amount) = 0;
    virtual void up(int amount) = 0;
    virtual void down(int amount) = 0;
    [[nodiscard]] virtual int calculate_position() const = 0;

    void execute_commands(Vec<String> &commands)
    {
        for (auto &command : commands) {
            auto split = command.trim_whitespace().split(' ');
            if (split.size() != 2)
                continue;

            if (split[0].trim_whitespace() == String("forward")) {
                forward(split[1].to_int().value_or(0));
            } else if (split[0].trim_whitespace() == String("down")) {
                down(split[1].to_int().value_or(0));
            } else if (split[0].trim_whitespace() == String("up")) {
                up(split[1].to_int().value_or(0));
            }
        }
    }
};

class BrokenElvishSubmarine : public Submarine {
public:
    void forward(int amount) override { m_horizontal += amount; }
    void up(int amount) override { m_depth -= amount; }
    void down(int amount) override { m_depth += amount; }
    [[nodiscard]] int calculate_position() const override { return m_horizontal * m_depth; }

private:
    int m_horizontal { 0 };
    int m_depth { 0 };
};

class ElvishSubmarine : public Submarine {
public:
    void forward(int amount) override
    {
        m_horizontal += amount;
        m_depth += m_aim * amount;
    }
    void up(int amount) override { m_aim -= amount; }
    void down(int amount) override { m_aim += amount; }

    [[nodiscard]] int calculate_position() const override { return m_horizontal * m_depth; }

private:
    int m_aim { 0 };
    int m_horizontal { 0 };
    int m_depth { 0 };
};

int part_one(char *buf)
{
    BrokenElvishSubmarine sub;
    Vec<String> commands = String(buf).split('\n');
    sub.execute_commands(commands);
    return sub.calculate_position();
}

int part_two(char *buf)
{
    ElvishSubmarine sub;
    Vec<String> commands = String(buf).split('\n');
    sub.execute_commands(commands);
    return sub.calculate_position();
}

// part-one: 2091984
// part-two: 2086261056
int main(int argc, char *argv[])
{
    Challenge challenge { "/home/spence/code/aoc/data/day2.txt", part_one, part_two };
    auto result = challenge.run(argc, argv);
    printf("%d", result);
    return 0;
}
