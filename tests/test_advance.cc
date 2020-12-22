#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto start = v.begin();
    for (size_t i = 0; i < v.size() / 3; ++i) {
        std::for_each(start, start + 3, [] (int& ii) {std::cout << ii << "\t";});
        std::advance(start, 3);
    }
    std::for_each(start, v.end(), [] (int& ii) {std::cout << ii << "\t";});
    return 0;

}