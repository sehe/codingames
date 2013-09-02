#include <iostream>
#include <string>
#include <map>
#include <set>
#include <iterator>
#include <algorithm>

using namespace std;

using DAG  = multimap<int, int>;
using Edge = DAG::value_type;

DAG readGraph()
{
	DAG edges;
	int n;
	if (cin >> n)
	{
		int pred, succ;
		while (n-- && (cin >> pred >> succ)) 
			edges.insert({pred,succ});

		if (cin || cin.eof())
			return edges;
	}
	exit(255);
}

int main()
{
	DAG edges = readGraph();

	map<int, int> visited;

	function<int(int node)> DFS = [&](int node) mutable
	{
		if (end(visited) == visited.find(node))
		{
			//cout << "visiting node " << node << "\n";
			auto const range = edges.equal_range(node);

			vector<int> lengths;
			transform(range.first, range.second, back_inserter(lengths),
					[&](Edge const& e) { return DFS(e.second); });

			visited[node] = 1 + (lengths.empty()? 0 : *max_element(begin(lengths), end(lengths)));
		} else
		{
			//cout << "skipping previously visited node " << node << "\n";
		}

		return visited[node];
	};

	set<int> preds, succs, roots;
	transform(begin(edges), end(edges), inserter(preds, end(preds)), [](Edge& e) { return e.first; });
	transform(begin(edges), end(edges), inserter(succs, end(succs)), [](Edge& e) { return e.second; });

	set_difference(
			begin(preds), end(preds),
			begin(succs), end(succs),
			inserter(roots, end(roots)));

	for (auto const& root : roots)
		DFS(root);

	auto longest = max_element(begin(visited), end(visited), 
            [](pair<const int, int> const& a, pair<const int, int> const& b) { return a.second < b.second; })->second;
	cout << longest;
}

