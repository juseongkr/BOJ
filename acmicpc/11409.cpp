#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;
#define MAX 400
const int src = 801, sink = 802;

class MCMF {
public:
	vector<vector<int>> capa, flow, dist, graph;
	int len;

	MCMF(int n) : len(n+2)
	{
		capa.resize(len);
		flow.resize(len);
		dist.resize(len);
		graph.resize(len);
		for (int i=0; i<len; ++i) {
			capa[i].resize(len);
			flow[i].resize(len);
			dist[i].resize(len);
		}
	}

	// return cost, flow
	pair<int, int> mcmf(int src, int sink)
	{
		int min_cost = 0, max_flow = 0;
		vector<int> prev(len), d(len);
		vector<bool> inque(len);

		while (1) {
			for (int i=0; i<len; ++i) {
				d[i] = INT_MAX;
				prev[i] = -1;
			}

			queue<int> que;
			d[src] = 0;
			inque[src] = 1;
			que.push(src);

			while (!que.empty()) {
				int cur = que.front();
				que.pop();
				inque[cur] = 0;
				for (int i=0; i<graph[cur].size(); ++i) {
					int next = graph[cur][i];
					if (capa[cur][next] - flow[cur][next] > 0 && \
					d[next] > d[cur] + dist[cur][next]) {
						d[next] = d[cur] + dist[cur][next];
						prev[next] = cur;
						if (!inque[next]) {
							que.push(next);
							inque[next] = 1;
						}
					}
				}
			}
			if (prev[sink] == -1)
				break;

			int f = INT_MAX;
			for (int i=sink; i!=src; i=prev[i])
				f = min(f, capa[prev[i]][i] - flow[prev[i]][i]);

			for (int i=sink; i!=src; i=prev[i]) {
				min_cost += f * dist[prev[i]][i];
				flow[prev[i]][i] += f;
				flow[i][prev[i]] -= f;
			}
			max_flow += f;
		}

		return {min_cost, max_flow};
	}

	void add_edge(int s, int e, int c, int d)
	{
		graph[s].push_back(e);
		graph[e].push_back(s);
		capa[s][e] += c;
		dist[s][e] += d;
		dist[e][s] -= d;
	}
};

int main()
{
	int n, m, k, x, y;

	cin >> n >> m;
	MCMF mm = MCMF(2*MAX+2);
	for (int i=0; i<n; ++i)
		mm.add_edge(src, i, 1, 0);

	for (int i=0; i<m; ++i)
		mm.add_edge(i+n, sink, 1, 0);

	for (int i=0; i<n; ++i) {
		cin >> k;
		while (k--) {
			cin >> x >> y;
			mm.add_edge(i, x+n-1, 1, -y);
		}
	}

	auto ans = mm.mcmf(src, sink);
	cout << ans.second << '\n' << -ans.first << '\n';

	return 0;
}
