add_library(sd sd/sd.cpp) # Temporary until I have a real .cpp file to stop cmake build errors
target_include_directories(sd PRIVATE sd)
target_include_directories(sd SYSTEM PUBLIC .)