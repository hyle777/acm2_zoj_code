#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;

const int N = 110;
int n, m;
double g[N][N];
double dist[N];
int st[N];

double dijkstra()
{

    memset(st, 0, sizeof st);
    memset(dist, 0, sizeof dist);
    dist[1] = 1;

    //每次迭代确定一个点的最短距离
    for (int i = 0; i < n - 1; i++)
    {
        // 在还未确定最短路的点中，寻找距离最小的点
        //可用堆优化
        int t = -1;
        for (int j = 1; j <= n; j++)
            if (!st[j] && (t == -1 || dist[t] < dist[j]))
                t = j;

        // 用t更新其他点的距离
        for (int j = 1; j <= n; j++)
            dist[j] = max(dist[j], dist[t] * g[t][j]);

        st[t] = true;
    }

    return dist[n];
}

int main()
{
    while (cin >> n && n)
    {
        cin >> m;
        memset(g, 0, sizeof g);
        int a, b, p;
        for (int i = 0; i < m; i++)
        {
            cin >> a >> b >> p;
            g[a][b] = g[b][a] = (double)p / 100;
        }
        printf("%.6f percent\n", dijkstra() * 100);
    }
    return 0;
}