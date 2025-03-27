#pragma once

#include "quick_sort.h" // partition
#include <cstddef> // size_t
#include <bits/stdc++.h> // std::swap
#include <cmath> // log2

template <typename T>
void insertion_sort(T *tab, size_t left, size_t right) {
    for (size_t i = left + 1; i <= right; i++) {  
        T key = tab[i]; 
        size_t j = i;
        
        while (j > left && tab[j - 1] > key) {
            tab[j] = tab[j - 1];
            j--;
        }
        
        tab[j] = key;
    }
}

template <typename T>
void heapify(T *tab, size_t left, size_t right, size_t root) {
    size_t s = root;  
    T val = tab[s];

    while (2 * (s - left) + 1 + left <= right) {
        size_t t = 2 * (s - left) + 1 + left;

        if (t + 1 <= right && tab[t + 1] > tab[t]) {t++;}
        if (val >= tab[t]) {break;}

        tab[s] = tab[t];
        s = t;
    }

    tab[s] = val;
}

template <typename T>
void heap_sort(T *tab, size_t left, size_t right) {
    size_t n = right - left + 1;

    for (size_t i = n / 2 + left; i-- > left;) {heapify(tab, left, right, i);}

    for (size_t i = right; i > left; i--) {
        std::swap(tab[left], tab[i]);
        heapify(tab, left, i - 1, left);
    }
}

template <typename T>
void intro_sort_util(T *tab, size_t left, size_t right, size_t max_depth) {
    size_t n = right - left + 1;
    if(n < 16) {insertion_sort(tab, left, right);}
    else if(max_depth == 0) {heap_sort(tab, left, right);}
    else {
        size_t p = partition(tab, left, right);
        intro_sort_util(tab, left, p - 1, max_depth);
        intro_sort_util(tab, p + 1, right, max_depth);
    }
}

template <typename T>
void intro_sort(T *tab, size_t left, size_t right) {
    size_t max_depth = std::log2(right - left + 1) * 2;
    intro_sort_util(tab, left, right, max_depth); // part of intro sort for recursion
}
