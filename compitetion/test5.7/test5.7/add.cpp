#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
typedef pair<ll, int> PLI;
const int N = 1.1e5 + 10; 
vector<PII> edges[N];
int n, m, k, s, e;
ll dist[N];
bool st[N];
void dijkstra() 
{
    for (int i = 0; i <= k * n + n; i++) dist[i] = 1e18;
    priority_queue<PLI, vector<PLI>, greater<PLI>> hp;
    hp.push({ 0, s });
    dist[s] = 0;
    while (hp.size()) {
        int x = hp.top().second;
        hp.pop();

        if (st[x]) continue;
        st[x] = true;

        for (auto& v : edges[x]) {
            int y = v.first;
            int w = v.second; 
            if (dist[x] + w < dist[y]) {
                dist[y] = dist[x] + w;
                hp.push({ dist[y], y });
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> k >> s >> e;

    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        edges[a].emplace_back(b, c);
        edges[b].emplace_back(a, c);

        for (int j = 1; j <= k; j++) {
            edges[a].emplace_back(b + n, 0);
            edges[b].emplace_back(a + n, 0);
            edges[a + n].emplace_back(b + n, c);
            edges[b + n].emplace_back(a + n, c);
            a += n;
            b += n;
        }
    }

    dijkstra();
    ll ret = 1e18;
    for (int i = 0; i <= k; i++) {
        ret = min(ret, dist[e + i * n]);
    }
    cout << ret << "\n";
    return 0;
}