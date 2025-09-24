#include <array>
#include <iostream>

template
<typename T, size_t N>
void print_array(const std::array<T, N>& arr) {
    std::cout << "[ ";
    for (auto i : arr) {
        std::cout << i << " ";
    }
    std::cout << "]\n";
}

int main() {

    std::array<int, 5> arr{1, 2, 3, 4, 5};

    print_array<int, 5>(arr);

    return 0;
}
