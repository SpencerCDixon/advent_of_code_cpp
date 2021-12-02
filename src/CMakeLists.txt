add_executable(day1 day1.cpp)
add_executable(day2 day2.cpp)

target_link_libraries(day1 PRIVATE sd)
target_link_libraries(day2 PRIVATE sd)