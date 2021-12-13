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
        REQUIRE(v.is_empty())
        v.append(true);
        EXPECT(!v.is_empty(), "is empty")
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

    // Pre-determined capacity
    {
        Vec<int> my_vec = Vec<int>::with_capacity(20, 0);
        EXPECT(my_vec.capacity() == 20, "can create vecs with capacity");
        for (auto &element : my_vec) {
            REQUIRE(element == 0);
        }
    }

    // Can clear a full vec
    {
        Vec<int> my_vec;
        for (int i = 0; i < 10; ++i)
            my_vec.append(i);

        REQUIRE(my_vec.size() == 10);
        my_vec.clear();
        REQUIRE(my_vec.size() == 0);
        REQUIRE(my_vec.capacity() == 0);
        PASS("can clear a full vec");
    }

    // Can remove the last element from a vector
    {
        static int times_popped { 0 };
        struct Poppable {
            Poppable()
                : value(0)
            {
            }
            ~Poppable()
            {
                times_popped++;
            }
            int value;
        };
        Vec<Poppable> my_vec;
        my_vec.append({});
        my_vec.append({});

        REQUIRE(my_vec.size() == 2);
        REQUIRE(times_popped == 3);
        my_vec.pop_last();
        REQUIRE(my_vec.size() == 1);
        EXPECT(times_popped == 4, "can remove element from array");
    }
}
