#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int N = 110;

int n, k;
vector<int> edges[N];
int in[N]; // 存入度信息

int main()
{
    cin >> n >> k;
    for (int i = 1; i <= k; i++)
    {
        int x, y;
        cin >> x >> y;
        //int j; cin >> i >> j;
        edges[x].push_back(y);
         in[y]++; // 统计入度信息
        
    }
    // 拓扑排序
    queue<int> q;
    for (int i = 1; i <= n; i++)
    {
        if (in[i] == 0) q.push(i);
    }
    queue<int> q1;
    while (q.size())
    {
        int x = q.front(); q.pop();
        q1.push(x);
        // 删除对应的边
        for (auto y : edges[x])
        {
            in[y]--;
            if (in[y] == 0) q.push(y);
        }
    }
    if (q.size())
    {
        cout << 2 << '\n';
        for (int i = 1; i <= n; i++)cout << i << " ";
        cout << '\n';
        for (int j = n; j >= 1; j--)cout << j << " ";
        cout << '\n';
    }
    else
    {
        cout << 1 << '\n';
        while (q1.size())
        {
            int x = q1.front(); q1.pop();
            cout << x << " ";
        }
        cout << '\n';
    }
    return 0;
}