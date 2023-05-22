#include <iostream>
#include <vector>
#include <omp.h>

void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    bool swapped;
    
    for (int i = 0; i < n - 1; ++i) {
        swapped = false;
        
        #pragma omp parallel for shared(arr, swapped)
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        
        if (!swapped) {
            break;
        }
    }
}

int main() {
    std::vector<int> data = {9, 2, 5, 1, 7, 3, 6, 4, 8}; // Input dataset

    std::cout << "Sequential Bubble Sort:\n";
    std::vector<int> seq_data = data; // Make a copy of the original data
    double seq_start = omp_get_wtime(); // Start time

    bubbleSort(seq_data); // Perform sequential bubble sort

    double seq_end = omp_get_wtime(); // End time
    double seq_duration = seq_end - seq_start; // Duration

    // Print the sorted data
    for (int num : seq_data) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "Sequential Bubble Sort Time: " << seq_duration << " seconds\n\n";

    std::cout << "Parallel Bubble Sort:\n";
    std::vector<int> par_data = data; // Make a copy of the original data
    double par_start = omp_get_wtime(); // Start time

    #pragma omp parallel
    {
        bubbleSort(par_data); // Perform parallel bubble sort
    }

    double par_end = omp_get_wtime(); // End time
    double par_duration = par_end - par_start; // Duration

    // Print the sorted data
    for (int num : par_data) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "Parallel Bubble Sort Time: " << par_duration << " seconds\n";

    return 0;
}
