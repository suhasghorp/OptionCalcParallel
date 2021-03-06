
cmake_minimum_required (VERSION 3.16)
project (OptionCalcParallel
    VERSION 0.1.0
    DESCRIPTION "A C++ Call Option Parallel Monte Carlo Pricer"
    LANGUAGES CXX
)

## Require C++11 for Catch2
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

## Add external dependencies here, e.g.:
## add_subdirectory(extern/example_sub_project)

## The directory for the library
add_subdirectory(src)

## Only build documentation if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    ## Docs only available if this is the main project
    find_package(Doxygen QUIET)
    if(Doxygen_FOUND)
        add_subdirectory(docs)
    else()
        message(STATUS "Doxygen not found, not building docs")
    endif()
    ## The example executable is only available for main project
    add_subdirectory(examples)
endif()

## Allow testing for main and subprojects if -DTESTS=TRUE
if(TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
