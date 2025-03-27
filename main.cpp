#include "merge_sort.h"
#include "quick_sort.h"
#include "intro_sort.h"
#include <iostream>

int main() {
    size_t SIZE = 9;
    int* arr = new int[SIZE] {5, 3, 1, 4, -2, -55, 0, 1, -2};
    for(size_t i = 0; i < SIZE; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    intro_sort(arr, 0, SIZE-1);
    for(size_t i = 0; i < SIZE; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    delete[] arr;
    return 0;
}