/**
 * 第十二周
 * dijkstra算法
 * 最短路的变形：
 * 分析：这题是最短路的变形，一般求的是路径总长的最小值，
 * 而此题是通路中最长边的最小值，每条边的权值可以通过坐标算出，
 * 因为是单源最短路径问题，所以我就简单使用Dijkstra算法了
 */
#include <iostream>
#include <string.h>
#include <algorithm>
#include <math.h>
#include <iomanip>
using namespace std;

const int N = 210;
const double maxv = 0x7fffffffffffffff;

struct node
{
    int x;
    int y;
} nod[N];

double d[N]; //存储源点到达该点的最长边的最短距离
int visit[N];

int n;

double count(int a, int b) //计算a，b两点的距离
{
    node na = nod[a], nb = nod[b];
    return sqrt((double)(na.x - nb.x) * (na.x - nb.x) + (double)(na.y - nb.y) * (na.y - nb.y));
}

void dijkstra()
{
    for (int i = 0; i < n; i++)
        d[i] = maxv;
    memset(visit, 0, sizeof(visit));
    d[0] = 0;
    //访问n遍
    for (int i = 0; i < n; i++)
    {
        int u = 0;
        double mind = maxv;
        //每次找到最小距离的点
        for (int j = 0; j < n; j++)
            if (!visit[j] && d[j] < mind)
            {
                u = j;
                mind = d[j];
            }
        visit[u] = 1;
        //用找到的点更新到其他点的距离
        for (int j = 0; j < n; j++)
            // d[j]=min(d[j],d[u]+count(u,j))
            d[j] = min(d[j], max(count(u, j), d[u]));
    }
}

int main()
{
    int num = 1;
    while (cin >> n && n != 0)
    {
        for (int i = 0; i < n; i++)
            cin >> nod[i].x >> nod[i].y;
        dijkstra();
        cout << "Scenario #" << num++ << endl;
        cout << "Frog Distance = " << fixed << setprecision(3) << d[1] << endl
             << endl;
    }
    system("pause");
    return 0;
}