#include <iostream>
#include <vector>
#include <omp.h>

void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> leftArr(n1);
    std::vector<int> rightArr(n2);

    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                mergeSort(arr, left, mid);
            }

            #pragma omp section
            {
                mergeSort(arr, mid + 1, right);
            }
        }

        merge(arr, left, mid, right);
    }
}

int main() {
    int n = 1000000; // Number of elements in the array
    std::vector<int> arr(n);

    // Initialize array with random values
    for (int i = 0; i < n; i++) {
        arr[i] = rand();
    }

    // Sequential Merge Sort
    std::vector<int> arrSequential = arr; // Create a copy for sequential sorting
    double startSequential = omp_get_wtime();
    mergeSort(arrSequential, 0, n - 1);
    double endSequential = omp_get_wtime();

    // Parallel Merge Sort
    std::vector<int> arrParallel = arr; // Create a copy for parallel sorting
    double startParallel = omp_get_wtime();
    mergeSort(arrParallel, 0, n - 1);
    double endParallel = omp_get_wtime();

    // Calculate execution times
    double timeSequential = endSequential - startSequential;
    double timeParallel = endParallel - startParallel;

    // Print results
    std::cout << "Sequential Merge Sort Time: " << timeSequential << " seconds\n";
    std::cout << "Parallel Merge Sort Time: " << timeParallel << " seconds\n";

    return 0;
}
