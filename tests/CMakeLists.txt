
include_directories(../extern/catch2)
include_directories(../extern)

add_executable(test_OptionCalcParallel test_OptionCalcParallel.cpp)

target_link_libraries(test_OptionCalcParallel PRIVATE OptionCalcParallel)

add_test(NAME OptionCalcParallel_test COMMAND test_OptionCalcParallel)
