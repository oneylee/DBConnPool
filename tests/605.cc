#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        vector<int> temp{1, 0};
        temp.insert(temp.end(), flowerbed.begin(), flowerbed.end());
        temp.emplace_back(0);
        temp.emplace_back(1);
        int distance = 0;
        auto last = temp.begin();
        for (auto it = temp.begin(); it != temp.end(); ++it) {
            if (it == last) continue;
            if (*it == 1) {
                distance += (std::distance(last, it) - 2) / 2;
                last = it;
            }
        }
        return distance >= n;
    }
};


int main()
{
    Solution ss;
    vector<int> vv{1, 0, 0, 0, 0, 0, 1};
    std::cout << ss.canPlaceFlowers(vv, 2) << std::endl;
    return 0;
}
