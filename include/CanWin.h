//https://leetcode.com/problems/nim-game/description/

class Solution {
public:
    static bool canWinNim(int n) {
        return (n % 4 != 0);
    }
};
