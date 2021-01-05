include_directories(../extern)
add_executable(example example.cpp)
target_link_libraries(example PRIVATE OptionCalcParallel)
