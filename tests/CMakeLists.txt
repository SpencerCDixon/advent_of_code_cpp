function(create_test name)
  add_executable(${name} ${name}.cpp)
  target_link_libraries(${name} sd)
endfunction()

create_test(TestVec)
create_test(TestRef)
create_test(TestOptional)
create_test(TestResult)
create_test(TestString)
create_test(TestHashMap)
create_test(TestStack)