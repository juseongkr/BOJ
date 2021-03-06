#include <iostream>
#include <vector>
using namespace std;
#define MAX 51

int n, k, x;
vector<int> graph[MAX];
int A[MAX], B[MAX];
bool visit[MAX];

bool dfs(int a)
{
	visit[a] = 1;
	for (int i=0; i<graph[a].size(); ++i) {
		int b = graph[a][i];
		if (B[b] == -1 || (!visit[B[b]] && dfs(B[b]))) {
			A[a] = b;
			B[b] = a;
			return true;
		}
	}
	return false;
}

int match()
{
	int ret = 0;
	fill(A, A+MAX, -1);
	fill(B, B+MAX, -1);
	for (int i=0; i<MAX; ++i) {
		fill(visit, visit+MAX, 0);
		if (dfs(i))
			ret++;
	}
	return ret;
}

int main()
{
	cin >> n >> k;
	for (int i=0; i<n; ++i) {
		cin >> x;
		for (int j=1; j<=n; ++j) {
			int y = j-x;
			if (y >= 0 && y % k == 0)
				graph[i].push_back(j-1);
		}
	}

	if (match() == n)
		cout << "1\n";
	else
		cout << "0\n";

	return 0;
}
