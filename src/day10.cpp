#include <aoc/Challenge.h>
#include <sd/Stack.h>
#include <sd/String.h>

int points_for_syntax_checker(char c)
{
    if (c == ')')
        return 3;
    if (c == ']')
        return 57;
    if (c == '}')
        return 1197;
    if (c == '>')
        return 25137;
    ASSERT_NOT_REACHED();
}
int points_for_autocomplete(char c)
{
    if (c == ')')
        return 1;
    if (c == ']')
        return 2;
    if (c == '}')
        return 3;
    if (c == '>')
        return 4;
    ASSERT_NOT_REACHED();
}

u64 points_for_closing_tag(String& tag)
{
    u64 value { 0 };
    for (size_t i = 0; i < tag.length(); ++i) {
        value *= 5;
        value += points_for_autocomplete(tag.characters()[i]);
    }
    return value;
}

bool is_opening(char c)
{
    return c == '(' || c == '[' || c == '{' || c == '<';
}
bool matches(char start, char end)
{
    return (start == '(' && end == ')') || (start == '[' && end == ']') || (start == '{' && end == '}') || (start == '<' && end == '>');
}
char matching_closing_tag(char c)
{
    if (c == '(')
        return ')';
    if (c == '[')
        return ']';
    if (c == '{')
        return '}';
    if (c == '<')
        return '>';
    ASSERT_NOT_REACHED();
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
                    points += points_for_syntax_checker(it);
                    break;
                }
            }
        }
    }

    printf("%lu\n", points);
    return 0;
}

int compare_u64(const void *elem1, const void *elem2)
{
    u64 f = *((u64 *)elem1);
    u64 s = *((u64 *)elem2);
    if (f > s)
        return -1;
    if (f < s)
        return 1;
    return 0;
}

int part_two(String &buf)
{
    Vec<String> lines = buf.split('\n');
    Vec<String> incomplete_lines;
    incomplete_lines.grow_capacity(lines.size());

    for (auto line : lines) {
        Stack<char> stack;
        bool is_corrupt { false };
        for (size_t i = 0; i < line.length(); ++i) {
            char it = line.characters()[i];
            if (is_opening(it)) {
                stack.push(it);
            } else {
                char last = stack.pop();
                if (!matches(last, it)) {
                    is_corrupt = true;
                    break;
                }
            }
        }

        if (!is_corrupt) {
            incomplete_lines.unchecked_append(line);
        }
    }

    ASSERT(incomplete_lines.size() != lines.size());
    Vec<u64> scores;
    scores.grow_capacity(incomplete_lines.size());

    for (auto line : incomplete_lines) {
        Stack<char> stack;
        for (size_t i = 0; i < line.length(); ++i) {
            char it = line.characters()[i];
            if (is_opening(it)) {
                stack.push(it);
            } else {
                stack.pop();
            }
        }

        size_t stack_size = stack.size();
        ASSERT(stack_size > 0);
        char tmp[stack_size + 1];
        tmp[stack_size] = '\0';
        for (size_t i = 0; i < stack_size; ++i) {
            tmp[i] = matching_closing_tag(stack.pop());
        }
        auto closing_tag = String(tmp);
        u64 points = points_for_closing_tag(closing_tag);
        scores.unchecked_append(points);
    }

    qsort(scores.data(), scores.size(), sizeof(u64), compare_u64);

    printf("%lu\n", scores.at(scores.size() / 2));
    return 0;
}

// part-one: 243939
// part-two: 2421222841
int main(int argc, char *argv[])
{
    Challenge challenge { "/home/spence/code/aoc/data/day10.txt", part_one, part_two };
    return challenge.run(argc, argv);
}
