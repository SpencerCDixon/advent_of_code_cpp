function(create_day name)
  add_executable(${name} ${name}.cpp)
  target_link_libraries(${name} PRIVATE sd aoc)
endfunction()

create_day(day1)
create_day(day2)
create_day(day3)
create_day(day4)
