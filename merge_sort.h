#pragma once

#include <cstddef> // size_t
#include <cstring> // std::memcpy

template <typename T>
void merge(T *tab, size_t left, size_t right, size_t middle) {
    size_t leftSize = middle - left + 1, rightSize = right - middle;
    T* leftArr = new T[leftSize];
    T* rightArr = new T[rightSize];
    
    std::memcpy(leftArr, &tab[left], leftSize * sizeof(T));
    std::memcpy(rightArr, &tab[middle + 1], rightSize * sizeof(T));
    size_t i = left, j = 0, k = 0;
    while(j < leftSize && k < rightSize) {tab[i++] = (leftArr[j] <= rightArr[k]) ? leftArr[j++] : rightArr[k++];} // add smaller and increment the trackers
    while(j < leftSize) {tab[i++] = leftArr[j++];} // add remaining elements, if there are any
    while(k < rightSize) {tab[i++] = rightArr[k++];} // add remaining elements, if there are any (there will always only be one side with remaining elements)
    
    delete[] leftArr;
    delete[] rightArr;
}

template <typename T>
void merge_sort(T *tab, size_t left, size_t right) {
    size_t middle = (left + right) / 2;
    if(left >= right) {return;} // if one element left
    merge_sort(tab, left, middle); // merge sort the left side
    merge_sort(tab, middle + 1, right); // merge sort the right side
    merge(tab, left, right, middle); // merge 2 sorted arrays
}