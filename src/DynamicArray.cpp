#include <DynamicArray.h>

// Constructor: initialize array with a default capacity
DynamicArray::DynamicArray(int initCapacity = 8){
    data = new Task[initCapacity];
}

// push_back: add a task to the end of the array