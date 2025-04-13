#pragma once

#include "quick_sort.h" // partition
#include "heap_sort.h"
#include "insertion_sort.h"
#include <cstddef> // size_t
#include <cmath> // log2

template <typename T>
void intro_sort_util(T *tab, size_t left, size_t right, size_t max_depth) {
    size_t n = right - left + 1;
    if(n < 16) {insertion_sort(tab, left, right);} // if size is <16 then perform the insertion sort (which is the best sorting algorithm for small arrays)
    else if(max_depth == 0) {heap_sort(tab, left, right);} // if size is bigger than 16 and the max depth has been reached, perform heap sort (to avoid O(n^2) worst-case of quick sort)
    // otherwise, perform one step of quicksort
    else {
        size_t p = partition(tab, left, right);
        if(p > left) {intro_sort_util(tab, left, p, max_depth - 1);}
        if(p + 1 < right) {intro_sort_util(tab, p + 1, right, max_depth - 1);}
    }
}

template <typename T>
void intro_sort(T *tab, size_t left, size_t right) {
    size_t max_depth = 2 * floor(std::log2(right - left + 1));
    intro_sort_util(tab, left, right, max_depth); // part of intro sort for recursion
}
