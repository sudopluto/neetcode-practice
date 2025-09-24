#include <iostream>
#include <string>
#include <vector>

template <typename T> using vector = std::vector<T>;
using string = std::string;

template <typename T>
void print_vec(const vector<T>& nums) {
    std::cout << "[ ";
    for (size_t i = 0; i < nums.size(); i++) {
        std::cout << (i == 0 ? "" : ", ") << nums[i];
    }
    std::cout << " ]\n";
}

class Solution {

public:

int remove_element(vector<int>& nums, int val) {
    print_vec(nums);
    return val;
}

};


int main() {

    Solution sol;

    std::cout << "\nex1: ";
    vector<int> ex1 = {1,1,2,3,4};
    print_vec(ex1);

    auto ret = sol.remove_element(ex1, 1);
    std::cout << "ex1 expected: [2,3,4]\n";
    std::cout << "ex1 ret expected: 3, acutal: " << ret << "\n";

    std::cout << "\nex2: ";
    vector<int> ex2 = {0,1,2,2,3,0,4,2};
    print_vec(ex2);
    ret = sol.remove_element(ex2, 2);
    std::cout << "ex2 expected: [0,1,3,0,4]\n";
    std::cout << "ex2 ret expected: 5, acutal: " << ret << "\n";

    return 0;
}
