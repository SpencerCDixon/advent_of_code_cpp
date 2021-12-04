set(SD_SOURCES
    sd/File.cpp
    sd/String.cpp
    )

set(AOC_SOURCES
    aoc/Challenge.cpp
    )

add_library(sd ${SD_SOURCES})
target_include_directories(sd PRIVATE sd)
target_include_directories(sd SYSTEM PUBLIC .)

add_library(aoc ${AOC_SOURCES})
target_link_libraries(aoc PRIVATE sd)
target_include_directories(aoc PRIVATE aoc)
target_include_directories(aoc SYSTEM PUBLIC .)