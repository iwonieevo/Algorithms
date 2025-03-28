#include "merge_sort.h"
#include "quick_sort.h"
#include "intro_sort.h"
#include <iostream>
#include <random>
#include <fstream>
#include <cstddef> // size_t
#include <cstring> // std::memcpy
#include <chrono>

void generate_random_data(int* arr, size_t N, int min, int max, float percentage){
    std::random_device rd; // random seed
    std::mt19937 gen(rd()); // generator
    std::uniform_int_distribution<int> dist(min, max); // range
    bool reversed = (percentage < 0);
    if(reversed) {percentage *= -1;}
    size_t n_sorted_data = N * percentage;
    if(!reversed) {for(size_t i = 0; i < n_sorted_data; i++) {arr[i] = i;}}
    else {for(size_t i = n_sorted_data; i > 0; i--) {arr[i] = i;}}
    
    for(size_t i = n_sorted_data; i < N; i++) {arr[i] = dist(gen);}
}

template <typename T>
unsigned long long measure_sorting_time(void (*sort)(T*, size_t, size_t), T *tab, size_t left, size_t right) {
    auto start = std::chrono::high_resolution_clock::now(); // start tracking time
    sort(tab, left, right);
    auto end = std::chrono::high_resolution_clock::now(); // stop tracking time
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    return duration.count();
}

int main() {
    size_t SIZES[] = {100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000}, N_TIMES = 100;
    float PERCENTAGES[] = {0, 0.25, 0.50, 0.75, 0.95, 0.99, 0.997, -1};
    int MIN = -10000, MAX = 10000;
    int *ref_arr, *copycat;
    unsigned long long counters[3][8] = {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}}; // [0][...] - MergeSort, [1][...] - QuickSort, [2][...] - IntroSort, [...][i] - PERCENTAGES[i]
    std::string OUT_PATH = "results.csv";
    std::ofstream out_file(OUT_PATH);
    if (!out_file.is_open()) {
        std::cerr << "Error: Could not open " << OUT_PATH << std::endl;
        return 1;
    }
    out_file << "SIZE;"
             << "MergeS - 0%;MergeS - 25%;MergeS - 50%;MergeS - 75%;MergeS - 95%;MergeS - 99%;MergeS - 99,7%;MergeS - sorted in reverse;"
             << "QuickS - 0%;QuickS - 25%;QuickS - 50%;QuickS - 75%;QuickS - 95%;QuickS - 99%;QuickS - 99,7%;QuickS - sorted in reverse;"
             << "IntroS - 0%;IntroS - 25%;IntroS - 50%;IntroS - 75%;IntroS - 95%;IntroS - 99%;IntroS - 99,7%;IntroS - sorted in reverse"
             << std::endl;

    for(auto SIZE : SIZES) {
        ref_arr = new int[SIZE];
        copycat = new int[SIZE];

        for(size_t i = 0; i < N_TIMES; i++) {
            for(size_t j = 0; j < 8; j++) {
                std::cout << "### SIZE=" << SIZE << " i=" << i << " PERCENTAGE=" << PERCENTAGES[j] << std::endl;
                generate_random_data(ref_arr, SIZE, MIN, MAX, PERCENTAGES[j]);

                std::cout << "MergeSort..." << std::endl;
                std::memcpy(copycat, ref_arr, SIZE * sizeof(int));
                counters[0][j] += measure_sorting_time(&merge_sort, copycat, 0, SIZE-1);
                for(size_t k = 1; k < SIZE; k++) {if(copycat[k] < copycat[k-1]) {std::cerr << "### FAIL @" << k << " POSITION" << std::endl; return 1;}}

                std::cout << "QuickSort..." << std::endl;
                std::memcpy(copycat, ref_arr, SIZE * sizeof(int));
                counters[1][j] += measure_sorting_time(&quick_sort, copycat, 0, SIZE-1);
                for(size_t k = 1; k < SIZE; k++) {if(copycat[k] < copycat[k-1]) {std::cerr << "### FAIL @" << k << " POSITION" << std::endl; return 1;}}

                std::cout << "IntroSort..." << std::endl;
                std::memcpy(copycat, ref_arr, SIZE * sizeof(int));
                counters[2][j] += measure_sorting_time(&intro_sort, copycat, 0, SIZE-1);
                for(size_t k = 1; k < SIZE; k++) {if(copycat[k] < copycat[k-1]) {std::cerr << "### FAIL @" << k << " POSITION" << std::endl; return 1;}}
            }
        }

        delete[] copycat;
        delete[] ref_arr;

        out_file << SIZE;
        for(size_t i = 0; i < 3; i++) {
            for(size_t j = 0; j < 8; j++) {
                out_file << ";" << counters[i][j] / N_TIMES;
                counters[i][j] = 0;
            }
        }
        out_file << std::endl;
    }

    out_file.close();
    return 0;
}