#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution
{
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode *root)
    {
        vector<vector<int>> result;
        if (!root) return result;
        vector<TreeNode*> temp, temp1;
        temp.emplace_back(root);
        vector<int> line{root->val};
        result.emplace_back();
        size_t i = 1;
        while(i) {
            vector<int> ll;

            if (i % 2) {
                if (temp.empty()) return result;
                for_each(temp.begin(), temp.end(), [&ll] (TreeNode* node) { ll.emplace_back(node->val); });
                result.emplace_back(ll);
                temp1.clear();
                for_each(temp.begin(), temp.end(), [&temp1] (TreeNode* node) { if (!node->right) temp1.emplace_back(node->right); if (!node->left) temp1.emplace_back(node->left); });
            } else {
                if (temp1.empty()) return result;
                for_each(temp1.begin(), temp1.end(), [&ll] (TreeNode* node) { ll.emplace_back(node->val); });
                result.emplace_back(ll);
                temp.clear();
                for_each(temp1.begin(), temp1.end(), [&temp] (TreeNode* node) { if (!node->left) temp.emplace_back(node->left); if (!node->right) temp.emplace_back(node->right); });
            }
            ++i;
        }
        return result;
    }
};