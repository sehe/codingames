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

vector<int> readHist()
{
    cin.clear();
    size_t number;
    cin >> number;

    vector<int> data;
    copy_n(istream_iterator<int>(cin), number, back_inserter(data));

    if (cin || cin.eof())
        return data;
    throw runtime_error("Failed to read history");
}

template <typename C>
vector<int> gen_diffs(C const& peaks)
{
    vector<int> diffs;
    for (auto a=begin(peaks); a!=end(peaks); ++a)
        for(auto b=next(a); b!=end(peaks); ++b)
            diffs.push_back(**b - **a);
    return diffs;
}

int main()
{
    auto const data = readHist();

    auto pair = minmax_element(begin(data), end(data));
    auto min_it = pair.first;
    auto max_it = pair.second;

    auto minaftermax  = min_element(max_it, end(data));
    auto maxbeforemin = max_element(begin(data), min_it);

    auto const diffs = gen_diffs(set<decltype(min_it)> { min_it, max_it, minaftermax, maxbeforemin });

    cout << min(0, *min_element(begin(diffs), end(diffs)));
}
