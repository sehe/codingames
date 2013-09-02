#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

using Phones = vector<string>;

int main()
{
    int n;
    if (cin >> n)
    {
        Phones index(n);
        copy_n(istream_iterator<string>(cin),n,begin(index));
        sort(begin(index), end(index));
        //

        unsigned nodes  = 0;
        string   prev;
        for (auto const& s : index)
        {
			prev.resize(20);
            auto where = mismatch(begin(s), end(s), begin(prev));
            auto matchlen = where.first - begin(s);

            nodes += s.size() - matchlen;

            prev = s;
        }

        cout << nodes;
    }
}
