#pragma once
#include <cstddef> // size_t

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