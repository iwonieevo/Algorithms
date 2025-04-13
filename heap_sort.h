#pragma once
#include <cstddef> // size_t
#include <bits/stdc++.h> // std::swap

template <typename T>
void heapify(T *tab, size_t left, size_t right, size_t root) {
    size_t s = root;
    T s_val = tab[s];

    while (2 * s - left + 1 <= right) {
        size_t t = 2 * s  - left + 1; // index of left child

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