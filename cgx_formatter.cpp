#include <iostream>
#include <iterator>
#include <cctype>

using namespace std;

int main()
{
    cin.ignore(1024, '\n'); // we don't check for input length, thanks
    istreambuf_iterator<char> in(cin), eof;
    ostreambuf_iterator<char> out(cout);

    enum { neutral, in_stringlit } state = neutral;

    bool bof         = true;
    bool nl_pending  = false;
    auto indentation = 0ul;

    auto newline = [&] () mutable {
        nl_pending = bof = false;
        *out++ = '\n';
        for (auto i=0u; i<indentation*4; ++i)
            *out++ = ' ';
    };

    auto emit = [&] (char ch) mutable {
        if (nl_pending && !bof) newline();
        bof = false;
        *out++ = ch;
    };
    auto copy = [&] () mutable { emit(*in++); };
    auto skip = [&] () mutable { in++; };
    //
    while (in != eof) switch(state) {
        case neutral:
            switch(*in) {
                case ' ' : case '\t': case '\r': case '\f':case '\n': skip(); break;
                case ';' : copy(); nl_pending = true; break;
                case '(' : nl_pending = true; copy(); ++indentation; nl_pending = true; break;
                case ')' : --indentation; nl_pending = true; copy(); break;
                case '\'': state = in_stringlit;
                default  : copy();
            }
            break;
        case in_stringlit:
            switch(*in) {
                case '\'': state = neutral;
                default  : copy();
            }
            break;
    }
}
