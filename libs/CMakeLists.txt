add_library(sd sd/String.cpp)
target_include_directories(sd PRIVATE sd)
target_include_directories(sd SYSTEM PUBLIC .)