#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
const int N = 1e3 + 10;
typedef pair<int, int> PII;
vector<int>a[N], b[N];
vector<PII>edges[N];
int dist[N];
bool st[N];
int n, m;
int s;
int cnt[N];
int v[N], u[N];
bool st1[N], st2[N];
bool spfa(int s)
{
	//cout << 1;
	for (int i = 0; i <= n; i++)
	{
		dist[i] = 1e9;
		st[i] = false;
		cnt[i] = 0;
   }
	queue<int>q;
	q.push(s);
	dist[s] = 0;
	st[s] = true;
	while (q.size())
	{
		int x = q.front(); q.pop();
		st[x] = false;
		for (auto& t : edges[x])
		{
			int y = t.first, z = t.second;
			if (dist[x] + z < dist[y])
			{
				dist[y] = dist[x] + z;
				cnt[y] = cnt[x] + 1;
				if (cnt[y] >= n + 1)return true;
				if (!st[y])
				{
					q.push(y);
					st[y] = true;
				}
			}
		}
	}
	return false;
}
void dfs1(int x)
{
	st1[x] = true;
	for (auto& y : a[x])
	{
		if(!st1[y])
		dfs1(y);
	}
}
void dfs2(int x)
{
	if (st1[x] == true)st2[x] = true;
	for (auto& y : a[x])
	{
		if (!st2[y])
			dfs2(y);
	}
}
int main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		cin >> v[i] >> u[i];
		a[v[i]].emplace_back(u[i]);
		b[u[i]].emplace_back(v[i]);
	}
	dfs1(1);
	dfs2(n);
	if (st1[n] == false)cout << -1 << '\n';
	else
	{
		for (int i = 1; i <= m; i++)
		{
			if (st2[v[i]] && st2[u[i]])
			{
				edges[v[i]].emplace_back(u[i], 9);
				edges[u[i]].emplace_back(v[i], -1);
			}
		}
	}
	spfa(1);
	cout << n << " " << m << '\n';
	for (int i = 1; i <= m; i++)
	{
		if (st2[u[i]] && st2[v[i]])
		{
			cout << u[i] << " " << v[i] << " " << dist[v[i]] - dist[u[i]] << '\n';

		}
		else
		{
			cout << u[i] << " " << v[i] << " " << 1 << '\n';
		}
	}
	return 0;
}