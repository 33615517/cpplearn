#include<iostream>
#include<map>
#include<unordered_map>
using namespace std;
#define int long long
int a[2000005];
const int INF = 1e9 + 7;

int pw(int x, int y)
{
    // 特判 0 和 1，防止无意义的循环和后续的除零风险
    if (x == 0)return 0;
    if (x == 1)return 1;
    int ans = 1;
    while (y)
    {
        if (y & 1)
        {
            // 2在累乘前进行除法预判。防止 ans *= x 瞬间溢出！
            if (INF / x < ans)return INF;
            ans *= x;
        }
        // 3
        // 如果 x 已经超过 INF，再执行 x *= x 必定会溢出 long long 甚至回绕变成 0
        if (x > INF)
        {
            x = INF + 1;
        }
        else
        {
            x *= x;
        }
        y >>= 1;
    }
    return ans;
}
signed main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        int f2 = 0;
        unordered_map<int, int>v;
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
            v[a[i]]++;
            if (v[a[i]] >= 2 && a[i] != 1)
            {
                f2 = 1;
            }
        }
        if ((f2 && v[1]) || v[1] >= 2)
        {
            cout << "YES" << '\n';
            continue;
        }
        int f = 0;
        for (int i = 0; i < n && f == 0; i++)
        {
            if (a[i] == 1)
                continue;
            for (int j = 2; j <= 30; j++)
            {
                // 4
                // 必须确保我们要用的指数 j，在原数组里是真实存在的
                if (!v[j])continue;

                int k = pw(a[i], j);
                if (k == INF)
                    break;

                if (v[k])
                {
                    cout << "YES" << '\n';
                    f = 1;
                    break;
                }
            }
        }
        if (f == 0)
            cout << "NO" << '\n';
    }
}