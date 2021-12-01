#pragma once

#include <cstdint>
#include <cstddef>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
static_assert(sizeof(u8) == 1, "incorrect u8 size");
static_assert(sizeof(u16) == 2, "incorrect u16 size");
static_assert(sizeof(u32) == 4, "incorrect u32 size");
static_assert(sizeof(u64) == 8, "incorrect u64 size");

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;
static_assert(sizeof(s8) == 1, "incorrect s8 size");
static_assert(sizeof(s16) == 2, "incorrect s16 size");
static_assert(sizeof(s32) == 4, "incorrect s32 size");
static_assert(sizeof(s64) == 8, "incorrect s64 size");

typedef float f32;
typedef double f64;

constexpr unsigned KB = 1024;
constexpr unsigned MB = KB * KB;
constexpr unsigned GB = KB * KB * KB;
