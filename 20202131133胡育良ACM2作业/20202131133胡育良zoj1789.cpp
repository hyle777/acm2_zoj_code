//第六周 并查集
#include <iostream>
using namespace std;
const int N = 30010;
int parent[N];
int n, m;

int find(int x)
{
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}
int main()
{
    while (cin >> n >> m)
    {
        for (int i = 0; i < n; i++)
            parent[i] = i;
        if (!n && !m)
            break;
        for (int i = 0; i < m; i++)
        {
            int k, x, y;
            cin >> k >> x;
            for (int i = 1; i < k; i++)
            {
                cin >> y;
                parent[find(y)] = parent[find(x)];
            }
        }
        int ans = 1;
        int p0 = find(0);
        for (int i = 1; i < n; i++)
        {
            if (find(i) == p0)
                ans++;
        }
        cout << ans << endl;
    }
    system("pause");
}
