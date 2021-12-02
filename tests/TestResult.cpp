#include <sd/Result.h>
#include <sd/Test.h>

int main(int, char **)
{
    // Can create successful result
    {
        Result<int, char*> result(42);
        EXPECT(result.is_ok(), "can create a successful result");
        REQUIRE(result.value() == 42);
    }

    // Can create failed result
    {
        Result<int, char*> result("didn't work :-(");
        EXPECT(result.is_error(), "can create a failed result");
    }
}