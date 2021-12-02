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
        Result<int, char*> result((char*)"didn't work :-(");
        EXPECT(result.is_error(), "can create a failed result");
    }

    // Can create errors from errno
    {
        fopen("blah", "r");
        auto value = Error::from_errno(errno);
        EXPECT(strcmp(value.message(), "No such file or directory") == 0, "creates useful error messages");
    }
}