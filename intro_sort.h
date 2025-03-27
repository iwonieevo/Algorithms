#pragma once

#include "quick_sort.h" // partition
#include <cstddef> // size_t
#include <bits/stdc++.h> // std::swap
#include <cmath> // log2

template <typename T>
void insertion_sort(T *tab, size_t left, size_t right) {
    for (size_t i = left + 1; i <= right; i++) { 
        T key = tab[i]; // store value to insert
        size_t j = i;
        
        while (j > left && tab[j - 1] > key) { // go back and move elements to the right to make place for our insertion
            tab[j] = tab[j - 1];
            j--;
        }
        
        tab[j] = key; // insert the value in the correct place
    }
}

template <typename T>
void heapify(T *tab, size_t left, size_t right, size_t root) {
    size_t s = root;
    T s_val = tab[s];

    while (2 * s + 1 - left <= right) {
        size_t t = 2 * s + 1 - left; // index of left child

        if (t + 1 <= right && tab[t + 1] > tab[t]) {t++;} // if the right child is in bounds and is greater than left child then t <- index of right child (so t is the index of the greater child)
        if (s_val >= tab[t]) {break;} // if the parent is already larger than the bigger child, then the heap property is maintained, so we exit

        tab[s] = tab[t]; // otherwise, swap the bigger child position to the parent position
        s = t; // s moves down to t
    }
    // loop continues, so the s_val eventually will find it's place

    tab[s] = s_val;
}

template <typename T>
void heap_sort(T *tab, size_t left, size_t right) {
    size_t n = right - left + 1;

    for (size_t i = n / 2 + left; i-- > left;) {heapify(tab, left, right, i);} // building the heap

    for (size_t i = right; i > left; i--) {
        std::swap(tab[left], tab[i]); // swap root with the last unsorted element
        heapify(tab, left, i - 1, left); // reduce heap size and heapify new root to restore heap order
    }
}

template <typename T>
void intro_sort_util(T *tab, size_t left, size_t right, size_t max_depth) {
    size_t n = right - left + 1;
    if(n < 16) {insertion_sort(tab, left, right);} // if size is <16 then perform the insertion sort (which is the best sorting algorithm for small arrays)
    else if(max_depth == 0) {heap_sort(tab, left, right);} // if size is bigger than 16 and the max depth has been reached, perform heap sort (to avoid O(n^2) worst-case of quick sort)
    // otherwise, perform one step of quicksort
    else {
        size_t p = partition(tab, left, right);
        intro_sort_util(tab, left, p - 1, max_depth - 1);
        intro_sort_util(tab, p + 1, right, max_depth - 1);
    }
}

template <typename T>
void intro_sort(T *tab, size_t left, size_t right) {
    size_t max_depth = 2 * floor(std::log2(right - left + 1));
    intro_sort_util(tab, left, right, max_depth); // part of intro sort for recursion
}
