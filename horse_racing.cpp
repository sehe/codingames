#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <deque>

using namespace std;

using Ints = deque<int>;

int main()
{
    int n;
    if (cin >> n)
    {
        Ints strenghts(n);
        copy_n(istream_iterator<int>(cin),n,begin(strenghts));
        //

        sort(begin(strenghts), end(strenghts));

        auto current = strenghts.front();
        strenghts.pop_front();

        for (auto& s : strenghts)
        {
            auto tmp = s;
            s -= current;
            current = tmp;
        }

        cout << *min_element(begin(strenghts), end(strenghts));
    }
}
