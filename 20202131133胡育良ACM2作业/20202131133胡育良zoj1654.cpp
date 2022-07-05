#include <iostream>
#include <string.h>
using namespace std;

const int N = 60;

char map[N][N];
int T, n, m;

//存图
const int M = 100010;
int h[N * 25], e[M], ne[M], idx; //邻接表存储所有的边，匈牙利算法只用到第一个集合指向第二个集合的边

//添加边a->b
void add(int a, int b)
{
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

int match[N * 25]; //第二个集合匹配第一个集合的点是哪一个
bool st[N * 25];   //第二个集合点是否已匹配过
bool find(int x)
{
    for (int i = h[x]; i != -1; i = ne[i])
    {
        int j = e[i];
        if (!st[j])
        {
            st[j] = true;
            if (match[j] == 0 || find(match[j])) //如果还没匹配 或者匹配过的可以找到另一个匹配
            {
                match[j] = x;
                return true;
            }
        }
    }
    return false;
}

int n1;               //集合1的节点数（块数）
int x[N][N], y[N][N]; //存储图中位置属于行,列的哪个块号

//构造二分图
void build()
{
    //所有行被墙分割的块构成集合1 所有列被墙分割的块构成集合2
    int r = 1, c = 1;
    for (int i = 0; i < n; i++)
    {
        int j = 0;
        while (j < m)
        {
            while (map[i][j] == '#' && j < m)
                j++;
            while ((map[i][j] == 'o' || map[i][j] == '*') && j < m)
            {
                x[i][j] = r;
                j++;
            }
            if (map[i][j] == '#' || j >= m)
                r++;
        }
    }
    for (int i = 0; i < m; i++)
    {
        int j = 0;
        while (j < n)
        {
            while (map[j][i] == '#' && j < n)
                j++;
            while ((map[j][i] == 'o' || map[j][i] == '*') && j < n)
            {
                y[j][i] = c;
                j++;
            }
            if (map[j][i] == '#' || j>=n)
                c++;
        }
    }

    //行块：集合1 列块：集合2
    //如果行块和列块有公共空地 则添加一条边:行块指向列块
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (map[i][j] == 'o')
                add(x[i][j], y[i][j]);

    n1 = r - 1;
}

//变量初始化
void init()
{
    memset(h, -1, sizeof(h));
    idx = 0;
    memset(match, 0, sizeof(match));
}

int main()
{
    cin >> T;
    for(int num=1;num<=T;num++)
    {
        init();
        cin >> n >> m;
        for (int i = 0; i < n; i++)
            cin >> map[i];
        build();
      //   for (int i = 1; i <= 10; i++) {
      //    cout << i << ":";
      //    for (int j = h[i]; j!=-1; j = ne[j])
      //    {
      //        cout << e[j] << " ";
      //    }
      //    cout << endl;
      //}
        //匈牙利算法 找最大匹配
        int res = 0;
        for (int i = 1; i <= n1; i++)
        {
            memset(st, 0, sizeof(st)); //每趟开始前所有节点均未匹配
            if (find(i))
                res++;
        }
        cout << "Case :" << num << endl;
        cout << res << endl;
    }
    return 0;
}
  

