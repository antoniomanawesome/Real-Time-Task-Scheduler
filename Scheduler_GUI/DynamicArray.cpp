#include "DynamicArray.h"


DynamicArray::DynamicArray() : size(0), capacity(4) {
    data = new Task[capacity]; // Creating a task array in the heap
}


DynamicArray::~DynamicArray(){
    delete[] data; // Deleting the data to avoid memory leaks
}

void DynamicArray::resize(){
    capacity *= 2; // Increasing capacity and storing it into a new task variable to copy the old data over
    Task* new_data = new Task[capacity];
    for(int i = 0; i < size; i++){
        new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
}

void DynamicArray::push_back(const Task& task){ // Task& is const because I don't want to modify the original task and just want to put it in my container
    if(size == capacity) resize();
    data[size++] = task; // adds the task to the next element of the array
}

void DynamicArray::remove(int index){ // After removing a task at a given index, shift rest of the data and update size
    for(int i = index; i < size - 1; i++){
        data[i] = data[i + 1];
    }
    size--;
}

int DynamicArray::get_size() const { //get_size() is const because we don't want to modify any of the objects member variables we just want to know what size is
    return size;
}

int DynamicArray::get_capacity() const {
    return capacity;
}

Task& DynamicArray::operator[](int index){
    return data[index];
}

void DynamicArray::clear() {
    size = 0;
}