//第八周 伸展树
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct node
{
    node *child[2]; // 0 1 左右孩子
    node *par;
    int v, w;
    node()
    {
        child[0] = child[1] = 0;
        par = 0;
        v = 0;
        w = 1;
    }
};

node *root;
void printTree();

//基础函数：get rotate
//基本操作：splay insert kth printTree
int get(node *x) // x是左节点要右旋返回1 反之返回0
{
    if (x->par->child[0] == x)
        return 1;
    return 0;
}

void rotate(node *x, int d) // 0 1 左旋 右旋
{
    node *y = x->par;

    //维护两个旋转点的权值
    int t = y->w, tt = 0;
    if (x->child[d])
        tt = x->child[d]->w;
    y->w = y->w - x->w + tt;
    x->w = t;

    y->child[!d] = x->child[d];
    if (x->child[d])
        x->child[d]->par = y;

    x->par = y->par;
    if (y->par)
    {
        if (y->par->child[0] == y)
            y->par->child[0] = x;
        else
            y->par->child[1] = x;
    }

    x->child[d] = y;
    y->par = x;
}

void splay(node *x, node *y) //节点x调整到节点y为双亲的位置上
{
    int d;
    for (node *f = x->par; f != y; f = x->par)
    {
        if (f->par == 0)
        { //只有一个父亲节点 一次单旋结束
            rotate(x, get(x));
            break;
        }
        d = get(f);
        if (d == get(x))
            rotate(f, d);
        else
            rotate(x, !d);
        rotate(x, d);
    }
    if (y == 0)
        root = x;
}

//插入操作
void insert(int v)
{
    node *t = new node;
    t->v = v;
    if (root == 0)
    {
        root = t;
        return;
    }
    node *p = root, *fp = root;
    while (p)
    {
        fp = p;
        fp->w++;
        if (v < p->v)
            p = p->child[0];
        else
            p = p->child[1];
    }
    if (v < fp->v)
        fp->child[0] = t;
    else
        fp->child[1] = t;
    t->par = fp;
    splay(t, 0);
}

//查找排名为k的数
int kth(node *root, int k)
{
    int lsize = 0;
    if (root->child[0])
        lsize = root->child[0]->w;
    if (k == lsize + 1)
        return root->v;
    else if (k <= lsize)
        return kth(root->child[0], k);
    else
        return kth(root->child[1], k - lsize - 1);
}

void printTree()
{
    queue<node *> qu;
    qu.push(root);
    cout << root->v << endl;
    while (!qu.empty())
    {
        node *t = qu.front();
        qu.pop();
        for (int i = 0; i < 2; i++)
        {
            if (t->child[i])
            {
                cout << t->child[i]->v << " ";
                qu.push(t->child[i]);
            }
            else
                cout << -1 << " ";
        }
        cout << endl;
    }
    cout << "-----" << endl;
}

const int N = 32767;   //天数
const int A = 1000000; //随机数的范围
// const int N=10;
// const int A=10;
int main()
{
    /*测试各个函数
    for (int i = 0; i <= 4; i++)
    {
        insert(i);
        printTree();
    }
    int x;
    while (cin >> x)
        cout << kth(root,x) << endl;
    */
    int sum = 0;
    for (int i = 0; i < N; i++)
    {
        // 0-A之间的值
        int x = rand() % A;
        // cout << x << " ";
        insert(x);
        int minv = A + 1;
        //找左边最大
        if (root->child[0])
        {
            node *p = root->child[0];
            while (p->child[1])
                p = p->child[1];
            minv = root->v - p->v;
        }
        //找右边最小
        if (root->child[1])
        {
            node *p = root->child[1];
            while (p->child[0])
                p = p->child[0];
            minv = min(minv, p->v - root->v);
        }
        if (minv == A + 1)
            minv = 0;
        sum += minv;
    }
    cout << endl
         << sum << endl;
    system("pause");
    return 0;
}