#include <sd/Optional.h>
#include <sd/Test.h>

int main(int, char **)
{
    // Default is none
    {
        Optional<int> opt;
        EXPECT(opt.is_none(), "empty optionals are not storing anything");
    }

    // The value can be accessed
    {
        Optional<int> opt = Optional(42);
        EXPECT(opt.value() == 42, "optionals value can be extracted");
    }

    // Dtors of the underlying values get called
    static int g_count = 0;
    struct MemTracker {
        MemTracker() { g_count++; }
        ~MemTracker() { g_count--; }
        MemTracker(MemTracker const &) { g_count++; }
    };
    REQUIRE(g_count == 0);
    {
        Optional<MemTracker> maybe_tracker { MemTracker() };
        Optional<MemTracker> second_tracker = { MemTracker() };
        EXPECT(g_count == 2, "ctor/dtors get called properly");
    }
    REQUIRE(g_count == 0);

    // Can release a movable value
    class MoveableValue {
    public:
        MoveableValue(int v)
            : m_value(v) {};
        MoveableValue(MoveableValue &&other)
        {
            m_value = exchange(other.m_value, 0);
        }
        [[nodiscard]] int get() const { return m_value; }
    private:
        int m_value { 0 };
    };

    // Can move a value into an optional
    {
        MoveableValue my_value(42);
        Optional<MoveableValue> opt(move(my_value));
        EXPECT(opt.value().get() == 42, "we can move values into the optional");
        REQUIRE(my_value.get() == 0);
    }

    // Can move optionals
    {
        Optional<int> opt { 42 };
        Optional<int> second { move(opt) };
        EXPECT(opt.is_none(), "moved optional to a new location");
        REQUIRE(second.value() == 42);
    }

    // Can provide fallbacks
    {
        Optional<int> empty;
        int value = 10;
        value += empty.value_or(20);
        EXPECT(value == 30, "can provide fallbacks when unwrapping the value");

        Optional<int> non_empty { 10 };
        value = 10;
        value += empty.value_or(100);
        EXPECT(value == 20, "won't use the fallback if tracking a value");
    }
}