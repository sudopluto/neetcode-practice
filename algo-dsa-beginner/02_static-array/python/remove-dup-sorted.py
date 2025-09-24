class Solution:

    def removeDuplicates(self, nums: list[int]) -> int:
        if (len(nums) < 2):
            return len(nums)

        r_head = 1
        w_head = 0

        while (r_head < len(nums)):

            #print(f"r_head:{r_head}, w_head:{w_head}")
            if (nums[r_head] != nums[w_head]):
                nums[w_head + 1] = nums[r_head]
                w_head += 1

            r_head += 1

        del nums[w_head + 1:]
        return w_head + 1


    def removeDuplicates2(self, nums: list[int]) -> int:
        if len(nums) == 0:
            print(f"output: []")
            return 0

        r_head = 1
        w_head = 1

        while r_head < len(nums):
            if nums[r_head] == nums[w_head -1]:
                r_head += 1
            else:
                nums[w_head] = nums[r_head]

                r_head += 1
                w_head += 1

        nums = nums[:w_head]
        print(f"output: {nums}")
        return w_head

ex1 = [1,1,2,3,4]
ex1_out = [1,2,3,4]
ex1_ret = 4

ex2 = [2,10,10,30,30,30]
ex2_out = [2,10,30]
ex2_ret = 3

sol = Solution()
print()

ret = sol.removeDuplicates(ex1)
print(f"expected: {ex1_out}")
print(f"actual: {ex1}")
print(f"ex1 ret = {ret}")
print(f"expected: {ex1_ret}")
print()

ret = sol.removeDuplicates(ex2)
print(f"expected: {ex2_out}")
print(f"actual: {ex2}")
print(f"ex2 ret = {ret}")
print(f"expected: {ex2_ret}")
print()
