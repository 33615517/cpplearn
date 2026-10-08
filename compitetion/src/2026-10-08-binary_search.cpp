#include <algorithm>
#include <iostream>
#include <vector>

int binary_search_index(const std::vector<int>& values, int target) {
    int left = 0;
    int right = static_cast<int>(values.size()) - 1;
    while (left <= right) {
        const int middle = left + (right - left) / 2;
        if (values[middle] == target) {
            return middle;
        }
        if (values[middle] < target) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }
    return -1;
}

int main() {
    int count = 0;
    std::cin >> count;
    std::vector<int> values(count);
    for (int& value : values) {
        std::cin >> value;
    }
    std::sort(values.begin(), values.end());

    int target = 0;
    std::cin >> target;
    std::cout << binary_search_index(values, target) << '\n';
    return 0;
}
