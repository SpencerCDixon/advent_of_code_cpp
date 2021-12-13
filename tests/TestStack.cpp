#include <sd/Stack.h>
#include <sd/Test.h>

int main(int, char **)
{
    // Empty
    {
        Stack<int> stack;
        EXPECT(stack.is_empty(), "can return whether or not it's empty")
    }

    // Push
    {
        Stack<int> stack;
        stack.push(42);
        EXPECT(stack.size() == 1, "can push items onto the stack");
    }

    // Pop
    {
        Stack<int> stack;
        stack.push(42);
        auto result = stack.pop();
        REQUIRE(stack.size() == 0);
        EXPECT(result == 42, "can pop items off the stack");
    }
}