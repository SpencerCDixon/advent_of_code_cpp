#include <aoc/Challenge.h>
#include <sd/Stack.h>
#include <sd/String.h>

int points_for_char(char c)
{
    if (c == ')')
        return 3;
    if (c == ']')
        return 57;
    if (c == '}')
        return 1197;
    if (c == '>')
        return 25137;
    return -1;
}

bool is_opening(char c)
{
    return c == '(' || c == '[' || c == '{' || c == '<';
}
bool is_closing(char c)
{
    return c == ')' || c == ']' || c == '}' || c == '>';
}
bool matches(char start, char end)
{
    return (start == '(' && end == ')') || (start == '[' && end == ']') || (start == '{' && end == '}') || (start == '<' && end == '>');
}

int part_one(String &buf)
{
    Vec<String> lines = buf.split('\n');

    u64 points { 0 };
    for (auto line : lines) {
        Stack<char> stack;
        for (size_t i = 0; i < line.length(); ++i) {
            char it = line.characters()[i];
            if (is_opening(it)) {
                stack.push(it);
            } else {
                char last = stack.pop();
                if (!matches(last, it)) {
//                    printf("syntax error: got %c\n", it);
                    points += points_for_char(it);
                    break;
                }
            }
        }
    }

    printf("%lu\n", points);
    return 0;
}
int part_two(String &buf)
{
    printf("0\n");
    return 0;
}

// part-one: 243939
// part-two: 0
int main(int argc, char *argv[])
{
    Challenge challenge { "/home/spence/code/aoc/data/day10.txt", part_one, part_two };
    return challenge.run(argc, argv);
}
