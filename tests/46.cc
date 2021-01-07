#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        size_t len = nums.size();
        if (len < 2) {
            result.push_back(nums);
            return result;
        }
        vector<int> item;
        backtrack(nums, result, item);
        return result;
    }

    void backtrack(vector<int>& nums, vector<vector<int>>& result, vector<int>& item) {
        size_t size = nums.size();
        if (item.size() == size) {
            result.emplace_back(item);
            return;
        }

        for (size_t i = 0; i < size; ++i) {
            if (std::find(item.begin(), item.end(), nums[i]) != item.end()) {
                continue;
            }

            item.emplace_back(nums[i]);
            backtrack(nums, result, item);
            item.pop_back();
        }
    }
};

int main()
{

}