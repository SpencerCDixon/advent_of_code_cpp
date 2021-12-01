#pragma once

#include "Utility.h"

#include <cstdio>
#include <cassert>
#include <cstdlib>

#define PASS(msg) printf("[ " GREEN "PASS" RESET " ] " msg "\n")
#define FAIL(line) printf("[ " RED "FAIL" RESET " ] assertion failed on:" line "\n")

#define EXPECT(condition, msg) \
    ASSERT(condition);         \
    PASS(msg);

#define S1(x) #x
#define S2(x) S1(x)

#define REQUIRE(condition)      \
    do {                       \
        if (!(condition)) {    \
            FAIL(S2(__LINE__)); \
            assert(false);     \
        }                      \
    } while (0);\
