#include<iostream>
#include<vector>
#include<deque>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;

void cm() {
    int n;
    cin >> n;
    vector<int> a(n + 2);
    for (int i = 1; i <= n; i++) cin >> a[i];
    a[n + 1] = 0;
    deque<int>b;
    for (int i = 1; i <= n + 1; i++)
    {
        int p = a[i];
        while (b.size() && b.back() < p)
        {

        }
    }
    
}

int main() 
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) 
    {
        cm();
    }
    return 0;
}