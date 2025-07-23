#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <string>

#include "DynamicArray.h"

using namespace std;

// Testing the Dynamic Array and its functions

TEST_CASE("Push & Index", "[DynamicArray]"){
    DynamicArray tasks;
    DynamicArray::Task t1(1, 3, 50, 10); // ID, priority, period, next_run_time

    tasks.push_back(t1);
    DynamicArray::Task& t = tasks[0];
    REQUIRE(t.ID == 1);
    REQUIRE(t.priority == 3);
    REQUIRE(t.period == 50);
    REQUIRE(t.next_run_time == 10);
}

TEST_CASE("Get Size", "[DynamicArray]"){
    DynamicArray tasks;
    DynamicArray::Task t1(1, 3, 50, 10); // ID, priority, period, next_run_time
    DynamicArray::Task t2(2, 1, 30, 0);

    tasks.push_back(t1);
    tasks.push_back(t2);

    REQUIRE(tasks.get_size() == 2);
    
}

TEST_CASE("Resize", "[DynamicArray]"){
    DynamicArray tasks;
    DynamicArray::Task t1(1, 3, 50, 10); // ID, priority, period, next_run_time
    DynamicArray::Task t2(2, 1, 30, 0);
    DynamicArray::Task t3(2, 1, 30, 0);
    DynamicArray::Task t4(2, 1, 30, 0);
    DynamicArray::Task t5(2, 1, 30, 0);

    tasks.push_back(t1);
    tasks.push_back(t2);
    tasks.push_back(t3);
    tasks.push_back(t4);
    tasks.push_back(t5);
    
    REQUIRE(tasks.get_capacity() == 8);

}