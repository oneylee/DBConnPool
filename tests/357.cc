#include <iostream>
#include <algorithm>

class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        int max = std::pow(10, n);
        int result = 10;
        int count = 0;
        backtrack(result, count, max);
        return count;
    }

    void backtrack(int& result, int& count, int max) {
        if (result < max) {
            return;
        }

        for (size_t i = 0; i < 10; ++i) {
            
            int temp = result;
            bool iscontinue = true;
            while (temp)
            {
                iscontinue = false;
                if (i == temp % 10) {
                    iscontinue = true;
                    break;
                }
                temp /= 10;
            }
            if (iscontinue) continue;
            
            result *= 10;
            result += i;
            ++count;
            std::cout << result << std::endl;
            backtrack(result, count, max);
            result /= 10;
        }
    }
};


int main()
{
    Solution ss;
    std::cout << ss.countNumbersWithUniqueDigits(2) << std::endl;
    return 0;
}