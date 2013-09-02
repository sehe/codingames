// Read inputs from stdin. Write outputs to stdout.
#include <bitset>
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

using bs = bitset<100*7>;

int main()
{
    std::string line;
    std::getline(std::cin, line);

    if (cin || cin.eof())
    {
        bs bits;
        for (char ch:line)
        {
            bits <<=7 ;
            bits |= (unsigned long) (ch & 0x7F);
        }

        auto b = 7*line.size();
        auto current = true;
        bool first = true;
        while (b>0)
        {
            --b;
            if (first || (bits[b] != current))
            {
                current = bits[b];
                std::cout << (first?"":" ") << (current? "0 " : "00 ");
            }

            std::cout << "0";
            first = false;
        }
        //std::cout << bits << "\n";
    }
}
