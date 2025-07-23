#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "DynamicArray.h"

using namespace std;


TEST_CASE("Get Size", "[DynamicArray]"){
    DynamicArray tasks;
    DynamicArray::Task t1(1, 3, 50, 10); // ID, priority, period, next_run_time
    DynamicArray::Task t2(2, 1, 30, 0);

    tasks.push_back(t1);
    tasks.push_back(t2);

    REQUIRE(tasks.get_size() == 2);
    
}
