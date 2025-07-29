cmake_minimum_required(VERSION 3.24)
project(my_tests)

set(CMAKE_CXX_STANDARD 14)


#recommended by aman to match test environment
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

#pull in desired version of catch through cmake automatically, make it available
Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.4.0 # seems to work with CLion - if you run into problems, try an older version of catch2 v3
)
FetchContent_MakeAvailable(Catch2)

include_directories(src)
include_directories(test-unit)

#the first word is the name of the executble
# everything else are the files to include
add_executable(Main
        src/main.cpp # your main
        src/DynamicArray.cpp
        src/DynamicArray.h
        src/Scheduler.cpp
        src/Scheduler.h
        
        )

#this one doesn't include main, instead having your test.cpp
add_executable(Tests
        test/test.cpp # your test file
        src/DynamicArray.cpp
        src/DynamicArray.h
        src/Scheduler.cpp
        src/Scheduler.h
        
        )
        
target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain) #link catch to test.cpp file
# the name here must match that of your testing executable (the one that has test.cpp)

include(CTest)
include(Catch)
catch_discover_tests(Tests)