#include <vector>
#include <iostream>

using namespace std;

void Print(vector<vector<int>>& cc);
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        if (matrix.size() < 2) return;

        size_t len = matrix.size();
        int item = 0;
        for (size_t i = 0; i < len; ++i) {
            for (size_t j = i + 1; j < len; ++j) {
                item = matrix[i][j];
                matrix[i][j] = matrix[j][i];
                matrix[j][i] = item;
            }
        }

        Print(matrix);
        for (size_t i = 0; i < len; ++i) {
            for (size_t j = 0; j < len / 2; ++j) {
                item = matrix[i][j];
                matrix[i][j] = matrix[i][len - 1 - j];
                matrix[i][len - 1 - j] = item;
            }
        }
    }
};


void Print(vector<vector<int>>& cc) {
    size_t len = cc.size();
    for (size_t i = 0; i < len; ++i) {
        for (size_t j = 0; j < len; ++j) {
            std::cout << cc[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
int main()
{
    vector<vector<int>> cc{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Print(cc);
    Solution ss;
    ss.rotate(cc);
    Print(cc);
    return 0;
}
