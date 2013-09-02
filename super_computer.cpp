#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Job { unsigned start, end; };

using Jobs = vector<Job>;

Jobs readJobs()
{
	Jobs jobs;
	unsigned n;
	if (cin >> n)
	{
		unsigned start, days;
		while (n-- && (cin >> start >> days)) 
			jobs.push_back(Job {start,start+days-1} );

		if (cin || cin.eof())
		{
			sort(begin(jobs), end(jobs), [](Job const& a, Job const& b) { return a.end<b.end; });
			return jobs;
		}
	}
	exit(255);
}

int main()
{
	const Jobs jobs = readJobs();

	unsigned count = 0;
	int curr_end = -1;
	for (auto& job : jobs)
		if ((int) job.start > curr_end)
		{
			count++;
			curr_end = job.end;
		}

	cout << count;
}
