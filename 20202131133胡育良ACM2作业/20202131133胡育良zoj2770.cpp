#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

const int N = 1010;
int n, m;

struct edge
{
    int a;
    int b;
    int w; // a b 权值
};
vector<edge> edges;

int dist[N];
// 求1到n的最短路距离，如果无法从1走到n，则返回-1。
int bellman_ford() // true说明存在负环
{
    memset(dist, 0x3f, sizeof dist);
    dist[n] = 0;
    bool flag; // 判断一轮循环过程中是否发生松弛操作

    // 如果第n次迭代仍然会松弛三角不等式，就说明存在一条长度是n+1的最短路径，由抽屉原理，路径中至少存在两个相同的点，说明图中存在负权回路。
    for (int i = 0; i < n; i++)
    {

        flag = false;
        for (int j = 0; j < 2 * n + m; j++)
        {
            int a = edges[j].a, b = edges[j].b, w = edges[j].w;
            if (dist[b] > dist[a] + w)
            {
                dist[b] = dist[a] + w;
                flag = true;
            }
        }
        // 没有可以松弛的边时就停止算法
        if (!flag)
            break;
    }
    return flag;
}

int main()
{
    while (cin >> n >> m)
    {
        while (edges.size())
            edges.pop_back();
        for (int i = 1; i <= n; i++)
        {
            int x;
            cin >> x;
            edges.push_back({i - 1, i, x}); // C1<=x S1-S0<=x 构建0->1 权值x
            edges.push_back({i, i - 1, 0}); // 0<=S1-S0  构建边1->0 权值0
        }
        for (int i = 1; i <= m; i++)
        {
            int a, b, w;
            cin >> a >> b >> w;
            edges.push_back({b, a - 1, -w}); // Ca+Cb>=W Sb-S(a-1)>=w 构建边 b->a-1 权值为-w
        }
        if (!bellman_ford())
            cout << -dist[0] << endl;
        else
            cout << "Bad Estimations" << endl;
    }
    return 0;
}