#pragma once

#include <cstddef> // size_t
#include <bits/stdc++.h> // std::swap

template <typename T>
T median_of_three(T& a, T& b, T& c) {
    if((a <= b && b <= c) || (a >= b && b >= c)) {return b;} // if b in the middle
    if((b <= a && a <= c) || (b >= a && a >= c)) {return a;} // if a in the middle
    return c; // otherwise
}

template <typename T>
size_t partition(T *tab, size_t left, size_t right) {
    T pivot = median_of_three(tab[left], tab[(left + right) / 2], tab[right]); // choosing a pivot as a median of beggining, middle and end

    int i = left - 1, j = right + 1;
    while(true) {
        do {i++;} while(tab[i] < pivot); // find bigger element than pivot on the left side
        do {j--;} while(tab[j] > pivot); // find smaller element than the pivot on the right side

        if(i >= j) {return j;}

        std::swap(tab[i], tab[j]); // swap these elements
    }
}

template <typename T>
void quick_sort(T *tab, size_t left, size_t right) {
    while(left < right) {
        size_t p = partition(tab, left, right); // choose a pivot and move everything smaller than it to the left and everything bigger to the right
        if((p > left && (p - left < right - p + 1)) || (p + 1 > right)) {
            quick_sort(tab, left, p); // quick sort left side
            left = p + 1;
        }

        else {
            quick_sort(tab, p + 1, right); // quick sort right side
            right = p;
        }
    }
}