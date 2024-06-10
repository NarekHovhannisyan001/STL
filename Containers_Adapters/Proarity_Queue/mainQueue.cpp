#include "prority_queue.hpp"
#include <iostream>
#include <vector>

struct foo
{
    bool operator()(int a, int b) {
        return a % 10 < b % 10;
    }
};


int main() {
    Proarity_queue<int, foo> piq; //(std::vector<int>{3,4,5,1,10,-1});
    piq.push(34);
    piq.push(43);
    piq.push(50);
    piq.push(11);
    piq.push(10);
    piq.push(-13);

    while(!piq.empty()) {
        piq.display();
        piq.pop();
    }
}