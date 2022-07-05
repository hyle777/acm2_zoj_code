//第3周 stl编程
// zoj1965
// poj2567 ac
// prufer序列：每次删除叶子节点编号最小的，输出与它相连的节点编号
//根据prufer序列还原树
#include <iostream>
#include <string.h>
#include <string>
#include <stack>
using namespace std;

const int N = 51;
int h[N], e[N], ne[N], idx; //邻接表存树
int yezi[N];                // 状态为0表示叶子节点

void add(int a, int b)
{
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

void init()
{
    memset(h, -1, sizeof(h));
    idx = 0;
}

void dfs(int u) //类似前序遍历
{
    cout << "(" << u;
    for (int i = h[u]; i != -1; i = ne[i])
        dfs(e[i]);
    cout << ")";
}

int main()
{
    string s;
    while (getline(cin, s))
    {
        init();
        memset(yezi, 0, sizeof(yezi));
        stack<int> stk;
        int x = 0;
        for (int i = 0; s[i] != 0; i++)
        {
            if (s[i] >= '0' && s[i] <= '9')
            {
                x *= 10;
                x += s[i] - '0';
            }
            if (s[i] == ' ')
            {
                stk.push(x);
                x = 0;
            }
        }
        stk.push(x);

        //算法：
        //从后向前遍历每个节点 每次添加一个节点建树 则此时所有节点都看作叶子节点
        //如果前面的节点是叶子节点 添加为自己的子节点 否则在剩下的叶子节点挑选编号最大的
        int root = stk.top();
        yezi[root] = 1;
        int cur = root;
        int maxn = stk.size() + 1; //最大编号
        if (root == 0)
        {
            cout << "(1)" << endl;
            continue;
        }
        while (!stk.empty())
        {
            cur = stk.top(); //当前节点
            stk.pop();
            if (!stk.empty())
            {
                int fr = stk.top(); //前一个节点
                if (!yezi[fr])
                {
                    add(cur, fr);
                    yezi[cur] = 1;
                    yezi[fr] = 1;
                }
                else
                {
                    while (yezi[maxn] && maxn >= 1)
                        maxn--;
                    add(cur, maxn);
                    yezi[maxn] = 1;
                    yezi[cur] = 1;
                }
            }
        }
        while (yezi[maxn] && maxn >= 1)
            maxn--;
        add(cur, maxn);

        dfs(root);
        cout << endl;
        //遍历每个节点
        /*
        for (int i = 1; i <= len; i++)
        {
            cout << i << " " << endl;
            for (int j = h[i]; j != -1; j = ne[j])
            {
                cout << e[j] << " ";
            }
            cout << endl;
        }
        */
    }
    return 0;
}