class Solution:

    def removeElement(self, nums: list[int], val:int) -> int:
        # lets inchworm l2r

        r_head = 0
        w_head = 0

        while (r_head < len(nums)):
            if (nums[r_head] != val):
                nums[w_head] = nums[r_head]
                w_head += 1

            r_head += 1

        del nums[w_head:]
        return w_head

    def removeElement2(self, nums: list[int], val: int) -> int:
        # could also do solution where stack allocate temp array to copy valid elements in,
        # and then copy back valid entries back into orignal array
        # or could force a reorder

        # depends on what we are optimizing for

        if len(nums) == 0:
            return 0

        lr_head = 0
        rl_head = len(nums) - 1

        #lr advances, if encounters val then swaps with rl_head
        #rl_head points to furthest avail valid val for swap
        #at the end rl_head will be meet lr head at end of valid array
        while lr_head < rl_head:
            if nums[rl_head] == val:
                rl_head -= 1
            elif nums[lr_head] == val:
                nums[lr_head] = nums[rl_head]
                rl_head -= 1
            else:
                lr_head += 1


        # forgot edge case if entire array is made up of value to remove
        return 0 if lr_head == 0 else lr_head + 1



ex1 = [1,1,2,3,4]
ex1_out = [2,3,4]
ex1_ret = 3

ex2 = [0,1,2,2,3,0,4,2]
ex2_out = [0,1,3,0,4]
ex2_ret = 5

sol = Solution()
print()

print(f"ex1: {ex1}, removing: 1")
ret = sol.removeElement(ex1, 1)
print(f"expected: {ex1_out}")
print(f"actual: {ex1}")
print(f"expected: {ex1_ret}")
print(f"ex1 ret = {ret}")
print()

print(f"ex2: {ex2}, removing: 2")
ret = sol.removeElement(ex2, 2)
print(f"expected: {ex2_out}")
print(f"actual: {ex2}")
print(f"expected: {ex2_ret}")
print(f"ex2 ret = {ret}")
print()
