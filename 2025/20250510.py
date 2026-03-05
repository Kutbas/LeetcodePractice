class Solution(object):
    def isUnique(self, astr):
        """
        :type astr: str
        :rtype: bool
        """
        bitMap = 0
        for ch in astr:
            i = ord(ch) - ord("a")
            if (bitMap >> i) & 1:
                return False
            bitMap |= 1 << i
        return True

    def countAndSay(self, n):
        """
        :type n: int
        :rtype: str
        """
        ret = "1"
        for _ in range(1, n):
            tmp = ""
            left = 0
            length = len(ret)
            while left < length:
                right = left
                while right < length and ret[left] == ret[right]:
                    right += 1
                tmp += str(right - left) + ret[left]
                left = right
            ret = tmp
        return ret

    