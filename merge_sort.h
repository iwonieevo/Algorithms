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
    if(left >= right) {return;}
    
    for(size_t current_size = 1; current_size < (right - left + 1); current_size *= 2) {
        for(size_t sub_left = left; sub_left <= right - current_size; sub_left += 2*current_size) {
            size_t sub_middle = (sub_left + current_size - 1 <= right) ? sub_left + current_size - 1 : right;
            size_t sub_right = (sub_left + 2 * current_size - 1 <= right) ? sub_left + 2 * current_size - 1 : right;
            if(!(sub_middle - sub_left + 1 <= 0) && !(sub_right - sub_middle <= 0)) {merge(tab, sub_left, sub_right, sub_middle);}
        }
    }
}