
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int inf = 0x3f3f3f3f;
int tree[200521];

//建立点线段树，并将信息域设置为inf
void BuildTree(int i, int left, int right)
{
    tree[i] = inf; //起初所有节点置为+∞
    if (left == right)
        return; //点线段树return的状态

    int mid = (left + right) >> 1;
    BuildTree(i << 1, left, mid);
    BuildTree(i << 1 | 1, mid + 1, right);
}

//实时更新线段树，以确保下次查询时各节点的tree[i]是最优(小)值
void Update(int i, int pos, int val, int left, int right)
{ // i是线段树的节点序号，pos是已排序区间的端点值，val是表示到达pos所需最少的sorter数量
    if (tree[i] > val)
        tree[i] = val; //若新的val比旧的tree[i]中的值小，则将其更新
    if (left == right)
        return; //点线段树return的状态

    int mid = (left + right) >> 1; //向下维护
    if (pos <= mid)
        Update(i << 1, pos, val, left, mid);
    else
        Update(i << 1 | 1, pos, val, mid + 1, right);
}

//查询新输入的x~y区间中可以连接新sorter的最优(小)值并返回
int Inquiry(int i, int x, int y, int left, int right)
{ // x~y是新的sorter区间,left~right是线段树的跨度区间
    if (x <= left && y >= right)
        return tree[i]; //若x~y覆盖left~right区间，则返回tree[i]

    int ans1 = inf, ans2 = inf;
    int mid = (left + right) >> 1;
    if (x <= mid)
        ans1 = Inquiry(i << 1, x, y, left, mid);
    if (y > mid)
        ans2 = Inquiry(i << 1 | 1, x, y, mid + 1, right);
    return ans1 < ans2 ? ans1 : ans2;
}

//主函数
int main()
{
    int n, m;
    while (~scanf("%d%d", &n, &m))
    {
        BuildTree(1, 1, n);
        Update(1, 1, 0, 1, n); //将所有线段树种中为区间端点值为1的tree[i]值更新为0

        while (m--)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            int temp = Inquiry(1, x, y, 1, n);
            Update(1, y, ++temp, 1, n); //加入新的sorter，temp需要+1
        }

        printf("%d\n", Inquiry(1, n, n, 1, n));
    }

    return 0;
}