#include <string>
#include <vector>
#include <iostream>

using namespace std;

string GetPrefix(string& str1, string& str2) {
    size_t pos = 0;
    for (; pos < str1.length() && pos < str2.length(); ++pos) {
        if (str1[pos] != str2[pos]) break;
    }
    return str1.substr(0, pos);
}

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.size() == 0) return "";
        string result(strs[0]);
        for (auto& item : strs) {
            result = GetPrefix(result, item);
        }
        return result;
    }
};

int main()
{
    vector<string> cc{"flower","flow","flight"};
    Solution ss;
    auto rr = ss.longestCommonPrefix(cc);
    std::cout << rr << std::endl;
    return 0;
}