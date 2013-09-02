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

struct Building { intmax_t x, y; };

vector<Building> readBuildings()
{
    cin.clear();
    size_t number;
    cin >> number;

    vector<Building> data;
    intmax_t x,y;
    while ((cin>>x>>y) && number--)
        data.push_back({x, y});

    if (cin || cin.eof())
        return data;
    throw runtime_error("Failed to read history");
}

intmax_t ylengths(intmax_t aty, vector<intmax_t> const& ys) {
    return accumulate(begin(ys), end(ys), 0.0, [aty](intmax_t accum, intmax_t y) { return accum + abs(aty - y); });
}

intmax_t binary_approach(vector<intmax_t> const& ys) {

    function<intmax_t(size_t,size_t)> recurse = [&](size_t a, size_t b)
    {
        if (a==b) return ys[a];
        auto ata = ylengths(ys[a], ys);
        auto atb = ylengths(ys[b], ys);

        auto half = (b-a)/2;
        if (ata<atb) return recurse(a, a + half);
        else         return recurse(b - half, b);
    };

    return recurse(0, ys.size()-1);
}

int main()
{
    auto const data = readBuildings();

    auto by_x = [](Building const& a, Building const& b) { return a.x < b.x; };
    //auto by_y = [](Building const& a, Building const& b) { return a.y < b.y; };

    auto const x_extremes = minmax_element(begin(data), end(data), by_x);

    vector<intmax_t> ys(data.size());
    transform(begin(data), end(data), begin(ys), [](Building const& bld) { return bld.y; });

    sort(begin(ys), end(ys));
    auto best_y = binary_approach(ys);

    auto const x_required = (x_extremes.second)->x - (x_extremes.first)->x;
    auto const y_required = ylengths(best_y, ys);
    cout << x_required + y_required;
}
