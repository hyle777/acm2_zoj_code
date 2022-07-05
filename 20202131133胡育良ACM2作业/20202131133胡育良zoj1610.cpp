//第九周 线段树
#include <iostream>
#include <queue>
#include <string.h>
using namespace std;

//区间最大值：8000 节点数：2*8000-1

const int N = 20000;            //节点数 20000 调试：50
pair<pair<int, int>, int> d[N]; //区间 颜色
const int M = 8000;             //区间最大值 8000 调试：10
int lastcolor = -1;
int cnt[M];

//建立线段树
void build(int a, int b, int u)
{
    d[u].first.first = a;
    d[u].first.second = b;
    if (a == b)
        return;
    int mid = (a + b) / 2;
    build(a, mid, 2 * u);
    build(mid + 1, b, 2 * u + 1);
}

//颜色值为懒标记（修改的变量） -1表示无颜色 -2表示无懒标记
//[l,r]表示要修改的区间 [a,b]表示当前的区间 u表示节点编号 color表示修改的颜色
void draw(int l, int r, int a, int b, int u, int color)
{
    if (l <= a && b <= r)
    {
        d[u].second = color;
        return;
    }
    //有颜色标记且不为叶子节点就拆分 颜色标记下行
    if (d[u].second != -2 && a != b)
    {
        //颜色下行
        d[2 * u].second = d[u].second;
        d[2 * u + 1].second = d[u].second;
        d[u].second = -2;
    }
    int mid = (a + b) / 2;
    if (l <= mid)
        draw(l, r, a, mid, 2 * u, color);
    if (r > mid)
        draw(l, r, mid + 1, b, 2 * u + 1, color);
}

//后序遍历
void count(int u)
{
    if (u >= N)
        return;
    if (d[u].second == -2)
    {
        count(2 * u);
        count(2 * u + 1);
    }
    if (d[u].second != lastcolor && d[u].second != -2)
    {
        if (d[u].second != -1)
            cnt[d[u].second]++; //-1颜色不计数
        lastcolor = d[u].second;
    }
}

int main()
{
    build(0, M, 1);
    int n;
    while (cin >> n)
    {
        d[1].second = -1;
        memset(cnt, 0, sizeof(cnt));
        while (n--)
        {
            int l, r, color;
            cin >> l >> r >> color;
            draw(l, r - 1, 0, M, 1, color); //题目区间为左开右闭
        }
        count(1);
        for (int i = 0; i < M; i++)
            if (cnt[i])
                cout << i << " " << cnt[i] << endl;
        cout << endl;
    }
    return 0;
}