#include <iostream>
#include <algorithm>
#include "slice.h"

struct Node
{
    Node* next;
    int val;
    Node(Node* n, int v) : next(n), val(v) {}
};

struct ll
{
    Node* first;
    Node** last;
};

#define ll_init(l)          \
    (l)->first = nullptr;   \
    (l)->last = &(l)->first

int main()
{
    ll* l = new ll();
    ll_init(l);
    Node* n = new Node(nullptr, 1);
    *l->last = n;
    l->last = &n->next;
    Node* n1 = new Node(nullptr, 2);
    *l->last = n1;
    l->last = &n1->next;

    orz::Slice ss("abcdefghi");
    auto rr = ss.Split('c');
    std::for_each(rr.begin(), rr.end(), [] (const std::string& str) { std::cout << str << std::endl; });
    std::cout << "h" << std::endl;
    return 0;
}