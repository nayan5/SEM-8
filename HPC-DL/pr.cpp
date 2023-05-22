#include <iostream>
#include <vector>
#include <limits>
#include <omp.h>
using namespace std;

int main() {
    vector<int> data = {9, 2, 5, 1, 7, 3, 6, 4, 8}; // Input dataset

    // Initialize variables for reduction
    int min_value = numeric_limits<int>::max();
    int max_value = numeric_limits<int>::min();
    int sum_value = 0;

    #pragma omp parallel for reduction(min: min_value) reduction(max: max_value) reduction(+: sum_value)
    for (int i = 0; i < data.size(); ++i) {
        // Find the minimum value
        if (data[i] < min_value) {
            min_value = data[i];
        }

        // Find the maximum value
        if (data[i] > max_value) {
            max_value = data[i];
        }

        // Calculate the sum
        sum_value += data[i];
    }

    // Calculate the average
    double average_value = static_cast<double>(sum_value) / data.size();

    // Print the results
    std::cout << "Min Value: " << min_value << std::endl;
    std::cout << "Max Value: " << max_value << std::endl;
    std::cout << "Sum Value: " << sum_value << std::endl;
    std::cout << "Average Value: " << average_value << std::endl;

    return 0;
}
