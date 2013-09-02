// Read inputs from stdin. Write outputs to stdout.
#include <iostream>
#include <algorithm>
#include <iterator>
#include <tuple>

using namespace std;

int main()
{
    vector<int> v;

	int n;
	cin >> n;

    cin.ignore();
    std::copy_n(std::istream_iterator<int>(cin), n, std::back_inserter(v));

    std::sort(begin(v), end(v), [](int a, int b) { return make_tuple(abs(a), -a) < make_tuple(abs(b), -b); });
    if (v.empty())
        std::cout << 0;
    else
        std::cout << v.front();
}
