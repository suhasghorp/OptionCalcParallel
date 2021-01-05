# Find all headers in the project include folder
file(GLOB HEADERS CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/OptionCalcParallel/*.h")

# Make a static library (tradeoff of memory for better performance)
add_library(OptionCalcParallel STATIC EquityPriceGenerator.cpp MCEuroOptPricer.cpp ${HEADERS})

# Add an alias so the target can be used while building
add_library(OptionCalcParallel::OptionCalcParallel ALIAS OptionCalcParallel)

# Set the include directory for builds (tests, examples, etc) and for clients
target_include_directories(OptionCalcParallel PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

# Associate the include files with the target, so they will be installed
set_target_properties(OptionCalcParallel PROPERTIES PUBLIC_HEADER "${HEADERS}")

find_package (Threads REQUIRED)

#sudo apt install libtbb-dev
find_package(TBB REQUIRED tbb)

find_package(Boost COMPONENTS system REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

include_directories(../extern)

target_link_libraries(OptionCalcParallel ${CMAKE_THREAD_LIBS_INIT} ${TBB_IMPORTED_TARGETS} ${Boost_LIBRARIES})

add_compile_options(-Wall -Wextra -Wpedantic -Werror)

# Set install targets and destinations
install(TARGETS OptionCalcParallel
    EXPORT OptionCalcParallelTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include/OptionCalcParallel)

# Export additional install files (for clients using CMake)
install(EXPORT OptionCalcParallelTargets
    NAMESPACE OptionCalcParallel::
    FILE OptionCalcParallelConfig.cmake
    DESTINATION lib/cmake/OptionCalcParallel)

