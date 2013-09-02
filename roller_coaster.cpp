#include <iostream>
#include <vector>
#include <map>
#include <cstdint>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <cassert>

using namespace std;

struct Config
{
    size_t    next_offset;
    uintmax_t first_time_ride_number;
    uintmax_t first_time_dirhams_before;
};

using Memoize = map<size_t/*offset*/, Config>;

int main()
{
    uintmax_t seats,      // seats
              rides,      // count of rides
              num_groups; // num_groups/o groups

    if (cin >> seats >> rides >> num_groups)
    {
        vector<uintmax_t> groups(num_groups);
        copy_n(istream_iterator<uintmax_t>(cin), num_groups, begin(groups));

        assert(all_of(begin(groups), end(groups), [seats](uintmax_t g) { return g <= seats; }));

        size_t    offset  = 0;
        uintmax_t dirhams = 0;
        Memoize   cache;

        //
        for (size_t ride=0; ride<rides; )
        {
            auto hit = cache.find(offset);
            if (end(cache) != hit) // HAH, a cycle
            {
                auto const& config = hit->second;
                auto dirhams_in_cycle = dirhams - config.first_time_dirhams_before;
                auto rides_in_cycle   = ride    - config.first_time_ride_number;

                // do a 'quick' catch up for as many cycles as will fit
                auto cycles = (rides-ride) / rides_in_cycle;

                //cout << "cycle offset:" << offset << " at ride " << ride << " rides_in_cycle:" << rides_in_cycle << " dirhams_in_cycle:" << dirhams_in_cycle << "\n";

                // apply
                dirhams += dirhams_in_cycle * cycles;
                ride    += rides_in_cycle   * cycles;

                // if the cycle didn't fit any more, fall through to single ride branch
                if (cycles) continue;
            }
            {
                // populate a single ride
                auto      start_offset = offset;
                uintmax_t fill=0;
                uintmax_t groups_boarded=0;
                do {
                    if ((fill + groups[offset]) > seats)
                        break;

                    groups_boarded++;
                    fill += groups[offset];

                    offset = (offset + 1) % groups.size();
                } while (fill < seats && groups_boarded < groups.size());

                cache[start_offset] = { offset, ride, dirhams };

                dirhams += fill;
                ++ride;
            }
        }

        cout << dirhams;
    }
}
