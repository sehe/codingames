#include <iostream>
#include <locale>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <string>
#include <stdexcept>
#include <cassert>

using namespace std;

struct LongLat { 
    LongLat(std::string const& degLong, string const& degLat)
        : lng(deg2rad(mystrtod(degLong))),
          lat(deg2rad(mystrtod(degLat)))
    {
    }
    double lng, lat; 
  private:
    static double deg2rad(double deg) {
        static constexpr double PI = atan(1)*4;
        return deg * PI / 180.0;
    }
    static double mystrtod(string s)
    {
        auto pos = s.find_first_of(",");
        if (string::npos != pos)
            s[pos] = '.';
        return strtod(s.c_str(), nullptr);
    }
};

struct Record
{
    int id;
    std::string name, address, phone;
    LongLat longlat;
};

using File = vector<Record>;

std::vector<std::string> split(std::string const& line)
{
    vector<string> cols;
    istringstream iss(line);

    while (iss)
    {
        string v;
        std::getline(iss, v, ';');
        if (!iss)
            break;
        cols.push_back(std::move(v));
    }

    if (iss || iss.eof())
        return cols;
    throw runtime_error("Failed to parse record");
}

//static ostream& operator<<(ostream& os, LongLat const& ll) { return os << "LongLat[" << ll.lng << ";" << ll.lat << "]"; }

File readRecords()
{
    cin.clear();
    size_t number;
    cin >> number;
    cin.ignore(1024, '\n');

    File data;
    while (cin && number--)
    {
        string line;
        getline(cin, line);
        auto cols = split(line);

        assert(cols.size() >= 6);

        data.push_back({ atoi(cols[0].c_str()),
                cols[1], cols[2], cols[3], 
                { cols[4], cols[5] } } );

        if (!cin)
            throw runtime_error("Failed to parse record, " + to_string(number) + "remaining");
    }

    if (cin || cin.eof())
        return data;
    throw runtime_error("Failed to parse file");
}

double distance(LongLat const& a, LongLat const& b)
{
    auto x = (b.lng - a.lng) * cos((a.lat + b.lat)/2.0);
    auto y = (b.lat - a.lat);
    auto d = sqrt(x*x + y*y) * 6371;
    return d;
}

int main()
{
    //setlocale(LC_NUMERIC, "fr_FR"); // Doesn't work in codinggames... 
    setlocale(LC_NUMERIC, "C");
    LongLat loc = []
    {
        string lat,lng;
        if (!(cin >> lng >> lat)) 
            throw runtime_error("Failed to parse location lines");
        return LongLat { lng, lat };
    }();

    auto const data = readRecords();
    vector<double> dists(data.size());
    transform(begin(data), end(data), begin(dists), [loc](Record const& a) { return distance(a.longlat, loc); });

    auto match = min_element(begin(dists), end(dists));
    auto index = match - begin(dists);
    cout << data[index].name;
}
