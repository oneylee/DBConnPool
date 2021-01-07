#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> result;
        if (n < 1) return result;
        vector<string> table;
        backtrack(result, table, n);
        return result;
    }

    void backtrack(vector<vector<string>>& result, vector<string>& table, int row) {
        if (table.size() == row) {
            result.emplace_back(table);
            return;
        }

        for (size_t i = 0; i < row; ++i) {
            std::string item(row, '.');
            item[i] = 'Q';
            if (std::find(table.begin(), table.end(), item) != table.end()) continue;
            bool iscontinue = false;
            for (int m = i, n = i, k = table.size(); m >= 0, n < row, k >= 0; --m, ++n, --k) {
                if (m == i) continue;
                if (table[k][m] == 'Q' || table[k][n] == 'Q') {
                    iscontinue = true;
                    break;
                }
            }
            
            if (iscontinue) continue;

            table.emplace_back(item);
            backtrack(result, table, row);
            table.pop_back();
        }
    }
};


int main()
{
    Solution ss;
    auto rr = ss.solveNQueens(2);
    std::for_each(rr.begin(), rr.end(), [] (vector<string>& str) {
        std::for_each(str.begin(), str.end(), [] (string& cc) {std::cout << cc << std::endl; });
        std::cout << std::endl;
    });
    return 0;
}