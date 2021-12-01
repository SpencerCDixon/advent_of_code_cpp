#include <sd/Ref.h>
#include <sd/Test.h>

static size_t g_global_count = 0;
class MemTracker {
public:
    MemTracker() { g_global_count += 1; }
    ~MemTracker() { g_global_count -= 1; }
};

int main(int, char *[])
{
    // Objects get created when making a ref
    {
        REQUIRE(g_global_count == 0);
        Ref<MemTracker> shared = Ref<MemTracker>::make({});
        EXPECT(g_global_count == 1, "creating a ref uses memory");
    }
    REQUIRE(g_global_count == 0);

    // Duplicating refs doesn't duplicate underlying types
    {
        Ref<MemTracker> shared = Ref<MemTracker>::make({});
        auto second = shared;
        EXPECT(g_global_count == 1, "cloning refs won't allocate more memory");
    }
    REQUIRE(g_global_count == 0);

    // Stay alive until all refs are gone
    {
        Ref<MemTracker> shared = Ref<MemTracker>::make({});
        auto second = shared;
        shared.clear();
        EXPECT(g_global_count == 1, "removing one shared pointer keeps the object alive");
        second = nullptr;
        REQUIRE(g_global_count == 0);
    }

    // Pointers to underlying value are the same
    {
        Ref<MemTracker> shared = Ref<MemTracker>::make({});
        MemTracker *ptr_1 = shared.get();
        auto second = shared;
        MemTracker *ptr_2 = second.get();
        EXPECT(ptr_1 == ptr_2, "underlying pointers between instances match");
    }

    // Empty
    {
        Ref<int> empty;
        EXPECT(empty.empty(), "default constructed refs are empty");

        Ref<int> had_stuff = Ref<int>::make(42);
        auto stole_stuff = move(had_stuff);
        EXPECT(had_stuff.empty(), "moved from refs are empty");
    }

    // Deref operator convenience
    {
        Ref<int> meaning_of_life = Ref<int>::make(42);
        EXPECT(*meaning_of_life == 42, "can dereference the ref to get the underlying value");
    }

    // Can increment underlying value through ->
    {
        Ref<int> meaning_of_life = Ref<int>::make(42);
    }

    return 0;
}
