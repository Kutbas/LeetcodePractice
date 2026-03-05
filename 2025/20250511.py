import heapq


class Solution(object):
    def sortArray(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """

        def merge_sort(nums, left, right):
            if left >= right:
                return

            mid = left + (right - left) // 2
            merge_sort(nums, left, mid)
            merge_sort(nums, mid + 1, right)

            tmp = []
            cur1, cur2 = left, mid + 1
            while cur1 <= mid and cur2 <= right:
                if nums[cur1] <= nums[cur2]:
                    tmp.append(nums[cur1])
                    cur1 += 1
                else:
                    tmp.append(nums[cur2])
                    cur2 += 1

            while cur1 <= mid:
                tmp.append(nums[cur1])
                cur1 += 1

            while cur2 <= right:
                tmp.append(nums[cur2])
                cur2 += 1

            nums[left : right + 1] = tmp

        merge_sort(nums, 0, len(nums) - 1)
        return nums

    def lastStoneWeight(self, stones):
        """
        :type stones: List[int]
        :rtype: int
        """
        q = [-s for s in stones]
        heapq.heapify(q)

        while len(q) > 1:
            x = -heapq.heappop(q)
            y = -heapq.heappop(q)
            heapq.heappush(q, -(x - y))

        return -q[0] if q else 0
