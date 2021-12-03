set(SD_SOURCES
    sd/File.cpp
    sd/String.cpp
    )

add_library(sd ${SD_SOURCES})
target_include_directories(sd PRIVATE sd)
target_include_directories(sd SYSTEM PUBLIC .)