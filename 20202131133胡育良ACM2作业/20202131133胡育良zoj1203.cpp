#include <iostream>
#include <queue>
#include <math.h>
#include <iomanip>
using namespace std;

const int N = 110;

int n;
//顶点的坐标
struct vertix
{
    double x;
    double y;
} vtx[N];
//边
struct edge
{
    int a;
    int b;
    double w; // a b 权值
};
bool operator<(const edge &a, const edge &b)
{
    return a.w > b.w;
}

//堆存储所有的边
priority_queue<edge> eds;

//并查集
int p[N];
int find(int x)
{
    if (p[x] != x)
        p[x] = find(p[x]);
    return p[x];
}

//计算权值
double getw(int i, int j)
{
    return sqrt((vtx[i].x - vtx[j].x) * (vtx[i].x - vtx[j].x) + (vtx[i].y - vtx[j].y) * (vtx[i].y - vtx[j].y));
}

// kruskal 求最小生成树的权值和
double kruskal()
{
    int count = 0;    //已选择的边数
    double sum = 0.0; //权值和
    while (count < n - 1)
    {
        edge t = eds.top();
        eds.pop();
        int a = find(t.a), b = find(t.b);
        if (a != b)
        {
            p[a] = b;
            sum += t.w;
            count++;
        }
    }
    return sum;
}

int main()
{
    int num = 1;

    while (cin >> n && n)
    {
        //初始化并查集
        for (int i = 0; i < n; i++)
            p[i] = i;
        //初始化堆
        while (!eds.empty())
            eds.pop();

        for (int i = 0; i < n; i++)
            cin >> vtx[i].x >> vtx[i].y;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                eds.push({i, j, getw(i, j)});
        if (num != 1)
            cout << endl;

        printf("Case #%d:\nThe minimal distance is: %.2f\n", num++, kruskal());
    }
    return 0;
}