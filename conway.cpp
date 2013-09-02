#include <iostream>
#include <locale>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <set>
#include <stdexcept>
#include <cassert>

using namespace std;

using Ints = vector<int>;

Ints conway(Ints const& seq)
{
    Ints result;
    auto last = end(seq);
    for(auto it = begin(seq); it!=last;)
    {
        auto next = it+1;
        while (next!=last && *next == *it)
            ++next;

        result.push_back(next-it);
        result.push_back(*it);

        it = next;
    }

    return result;
}

int main()
{
    int r,l;
    if (cin >> r >> l)
    {
        Ints seq = {r};
        while (--l)
            seq = conway(seq);

        int first = 0;
        for(auto i : seq)
            cout << (first++?" ":"") << i;

        cout << "\n";
    }
}
