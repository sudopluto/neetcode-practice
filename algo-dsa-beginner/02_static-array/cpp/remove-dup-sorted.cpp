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

    int removeDuplicates(vector<int>& nums) {
        // 0 or 1 dont do anything
        if (nums.size() < 2) {
            return nums.size();
        }

        size_t r_head = 1;
        size_t w_head = 1;

        while (r_head < nums.size()) {
            if (nums[w_head - 1] != nums[r_head]) {
                nums[w_head] = nums[r_head];
                ++w_head;
            }
            ++r_head;
        }

        nums.resize(w_head);

        print_vec(nums);
        return w_head;

    }

    int removeDuplicates_old(vector<int>& nums) {
        if (nums.size() == 0) {
            std::cout << "[ ]\n";
            return 0;
        }

        int k = 1;
        size_t r_head = 1;
        size_t w_head = 1;

        while (r_head < nums.size()) {
            if (nums[r_head] == nums[w_head - 1]) {
                r_head++;
            } else {
                nums[w_head] = nums[r_head];
                r_head++;
                w_head++;
                k++;
            }
        }


        nums.resize(w_head);
        print_vec(nums);

        return k;
    }
};

int main() {

    Solution sol;

    std::cout << "\nex1: ";
    vector<int> ex1 = {1,1,2,3,4};
    print_vec(ex1);

    auto ret = sol.removeDuplicates(ex1);
    std::cout << "ex1 expected: [1,2,3,4]\n";
    std::cout << "ex1 ret expected: 4, acutal: " << ret << "\n";

    std::cout << "\nex1: ";
    vector<int> ex2 = {2,10,10,30,30,30};
    print_vec(ex2);
    ret = sol.removeDuplicates(ex2);

    std::cout << "ex2 expected: [2,10,30]\n";
    std::cout << "ex2 ret expected: 3, acutal: " << ret << "\n";

    return 0;
}
