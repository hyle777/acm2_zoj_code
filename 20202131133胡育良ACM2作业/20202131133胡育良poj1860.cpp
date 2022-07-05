#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
const int N = 210;

int n, m, s; //货币种类数（点） 兑换点数量（边） s 拥有的货币种类（起点）
float v;     //拥有的货币数量

struct edge
{
    int a;
    int b;
    float r;
    float c; // a->b rab cab
};
vector<edge> eds;
float dist[N]; //每个点的货币数量

int bellman_ford()
{
    memset(dist, 0, sizeof dist);
    dist[s] = v;
    bool flag; // 判断一轮循环过程中是否发生松弛操作

    // 如果第n次迭代仍然会松弛三角不等式,则会继续更新，说明图中存在正环
    for (int i = 1; i <= n; i++)
    {

        flag = false;
        for (int j = 0; j < 2 * m; j++)
        {
            int a = eds[j].a, b = eds[j].b;
            float r = eds[j].r, c = eds[j].c;
            if ((dist[a] - c) * r > dist[b])
            {
                dist[b] = (dist[a] - c) * r;
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

    while (cin >> n >> m >> s >> v)
    {
        for (int i = 0; i < m; i++)
        {
            int a, b;
            float rab, cab, rba, cba;
            //每行六个数，整数a和b表示两种货币，a到b的汇率，a到b的佣金，b到a的汇率，b到a的佣金
            cin >> a >> b >> rab >> cab >> rba >> cba;
            eds.push_back({a, b, rab, cab});
            eds.push_back({b, a, rba, cba});
        }
        if (bellman_ford())
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}