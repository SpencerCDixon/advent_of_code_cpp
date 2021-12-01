#include <sd/Test.h>
#include <sd/Types.h>
#include <sd/Vec.h>

int main(int, char **)
{
    {
        Vec<u8> v;

        u8 second_value = 60;
        v.append(42);
        v.append(second_value);
        v.append(3);

        REQUIRE(v[0] == 42);
        REQUIRE(v[1] == 60);
        REQUIRE(v.at(2) == 3);
        PASS("append()");
    }

    // Empty
    {
        Vec<bool> v;
        EXPECT(v.is_empty(), "is empty")
    }

    // First/Last
    {
        Vec<int> v;
        v.append(1);
        v.append(2);
        v.append(3);
        EXPECT(v.first() == 1, "first()")
        EXPECT(v.last() == 3, "last()")
    }

    // Contains
    {
        Vec<int> v { 1, 2, 42, 4, 5 };
        EXPECT(v.contains_slow(42), "contains_slow()")
    }

    // Copy Constructor
    {
        Vec<int> v1 { 1, 2, 3 };
        auto v2 = v1;
        REQUIRE(v1.first() == 1);
        REQUIRE(v2.first() == 1);
        PASS("copy constructor");
    }

    // Move Constructor
    {
        Vec<int> v1 { 1, 2, 3 };
        auto v2 = move(v1);
        REQUIRE(v1.is_empty());
        REQUIRE(v2.first() == 1);
        PASS("move constructor");
    }

    // Iteration
    {
        int sum = 0;
        Vec<int> v1 { 1, 2, 3 };

        for (auto &val : v1)
            sum += val;

        EXPECT(sum == 6, "iteration");
    }
}
