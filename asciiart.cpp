#include <cctype>
#include <bitset>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <tuple>

using namespace std;

using bs = std::bitset<100*8>;

int main()
{
    std::string line;
    std::getline(std::cin, line);

    if (cin || cin.eof())
    {
        bs bits;
        for (char ch:line)
        {
            bits <<=8 ;
            bits &= (unsigned long) (ch & 0x7F);
        }

    }
}
