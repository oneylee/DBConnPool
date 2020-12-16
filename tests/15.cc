#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        std::sort(nums.begin(), nums.end());
        size_t len = nums.size();
        if (len < 3) return result;
        
        for (size_t i = 0; i < len - 2; ++i) {
            size_t j = i + 1, k = len - 1;
            while (j < k) {
                if (nums[i] + nums[j] + nums[k] < 0) {
                    ++j;
                    while (nums[j] == nums[j - 1] && j < k) {
                        ++j;
                    }
                } else if (nums[i] + nums[j] + nums[k] > 0) {
                    --k;
                    while (nums[k] == nums[k + 1] && j < k) {
                        --k;
                    }
                } else {
                    vector<int> item{nums[i], nums[j], nums[k]};
                    std::cout << i << "\t" << j << "\t" << k << std::endl;
                    result.emplace_back(item);
                    ++j;
                    while (nums[j] == nums[j - 1] && j < k) {
                        ++j;
                    }
                }
            }
            while (nums[i + 1] == nums[i] && i < len - 2)
            {
                ++i;
            }
            
        }
        return result;
    }
};


int main()
{
    vector<int> cc{-1, 0, 1, 2, -1, -4};
    Solution ss;
    auto rr = ss.threeSum(cc);
    for_each(rr.begin(), rr.end(), 
        [] (vector<int>& item) {
            std::cout << "[";
            for_each(item.begin(), item.end(), 
                [] (int & ele) {
                    std::cout << ele << "\t";
                });
            std::cout << "]" << std::endl;
        });

    return 0;
}