#include "DynamicArray.h"
#include <iostream>

int main(){
    DynamicArray tasks;
    DynamicArray::Task t1(1, 3, 50, 10); // ID, priority, period, next_run_time
    DynamicArray::Task t2(2, 1, 30, 0);

    tasks.push_back(t1);
    tasks.push_back(t2);

    std::cout << tasks.get_size();

    return 0;
}