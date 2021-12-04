#include <sd/Utility.h>
#include <sd/String.h>
#include <sd/HashMap.h>
#include <sd/Test.h>

int main(int, char**)
{
    // Can insert and retrieve values
    {
        HashMap<String, int> map;
        map.insert("key1", 20);
        map.insert("key2", 40);
        REQUIRE(*map.get("key1") == 20);
        REQUIRE(*map.get("key2") == 40);

        HashMap<String, Vec<String>> complex;
        complex.insert("key", Vec({ String("one"), String("two") }));
        auto returned_vec = complex.get("key");
        REQUIRE(returned_vec->first() == "one");
        REQUIRE(returned_vec->second() == "two");
        PASS("HashMap can insert and retrieve values");
    }
}