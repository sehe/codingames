// Read inputs from stdin. Write outputs to stdout.
#include <iostream>
#include <algorithm>
#include <iterator>
#include <map>
#include <functional>
#include <cstring>

using namespace std;

// case-independent (ci) compare_less binary function
struct ci_less
{
    bool operator() (const unsigned char& c1, const unsigned char& c2) const {
        return tolower (c1) < tolower (c2); 
    }
    bool operator() (const std::string & s1, const std::string & s2) const {
        return std::lexicographical_compare 
            (s1.begin (), s1.end (),
             s2.begin (), s2.end (), *this);
    }
};

int main()
{
    map<string, string, ci_less> reg;

    int N,Q;
    if (cin >> N >> Q)
    {
        while (N-- && cin)
        {
            std::string ext, mimetype;
            if (cin >> ext >> mimetype)
                reg[ext] = mimetype;
            else return 255;
        }
    }

    cin.ignore(1024, '\n');

    while (cin && Q--)
    {
        string fname;
        std::getline(cin, fname);

        if (!cin) return 255;

        auto pos = fname.find_last_of(".");
        if (string::npos != pos)
        {
            auto ext = fname.substr(pos+1);
            auto match = reg.find(ext);
            if (match == reg.end())
                cout << "UNKNOWN" << "\n";
            else
                cout << reg[ext] << "\n";
        } else
        {
            cout << "UNKNOWN" << "\n";
        }
    }
}
