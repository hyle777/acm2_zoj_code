/**
 * 第11周 拓扑排序
 * 分析：
 * 通过题目条件建图：存储每个框的左上右下坐标  用邻接数组存储图
 * 拓扑排序：输出每种拓扑排序（全排序问题）采用dfs算法 注意回溯的语句
 *
 */
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;

const int N = 31;
const int M = 27;
char map[N][N];

struct node
{
    int x1;
    int y1;
    int x2;
    int y2;
} pos[M]; //左上和右下坐标

int n, m;

int table[N][N]; //存图

int exist[M]; //某点是否存在 A-Z 0-25

int in[M]; //入度

queue<int> qu;   //拓扑排序的队列
vector<int> ans; //存储拓扑排序的答案

int cnt;

void init()
{
    ans.clear();
    memset(table, 0, sizeof(table));
    memset(exist, 0, sizeof(exist));
    memset(in, 0, sizeof(in));
    for (int i = 0; i < M; i++)
    {
        pos[i].x1 = 100;
        pos[i].y1 = 100;
        pos[i].x2 = -1;
        pos[i].y2 = -1;
    }
}

//确定边框的位置 左上和右下节点坐标
void initPos()
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            if (map[i][j] == '.')
                continue;
            int x = map[i][j] - 'A';
            exist[x] = 1;
            if (i < pos[x].x1)
                pos[x].x1 = i;
            if (j < pos[x].y1)
                pos[x].y1 = j;
            if (i > pos[x].x2)
                pos[x].x2 = i;
            if (j > pos[x].y2)
                pos[x].y2 = j;
        }
}

//构图
void initIn()
{
    for (int i = 0; i < M; i++)
    {
        if (exist[i])
        {
            //左右两边
            for (int j = pos[i].x1; j <= pos[i].x2; j++)
            {
                int t = map[j][pos[i].y1] - 'A';
                if (t != i && table[i][t] == 0)
                {
                    table[i][t] = 1;
                    in[t]++;
                }
                t = map[j][pos[i].y2] - 'A';
                if (t != i && table[i][t] == 0)
                {
                    table[i][t] = 1;
                    in[t]++;
                }
            }
            //上下两边
            for (int j = pos[i].y1; j <= pos[i].y2; j++)
            {

                int t = map[pos[i].x1][j] - 'A';
                if (t != i && table[i][t] == 0)
                {
                    table[i][t] = 1;
                    in[t]++;
                }
                t = map[pos[i].x2][j] - 'A';
                if (t != i && table[i][t] == 0)
                {
                    table[i][t] = 1;
                    in[t]++;
                }
            }
        }
    }
}

//拓扑排序 dfs算法
int toposortDfs()
{
    if (ans.size() == cnt)
    {
        for (int i = 0; i < ans.size(); i++)
            cout << char('A' + ans[i]);
        cout << endl;
        return true;
    }
    for (int i = 0; i < M; i++)
    {
        //每次找到入度为0的点
        if (exist[i] && in[i] == 0)
        {
            ans.push_back(i);
            in[i] = -1;

            //相邻边删去 相邻点的入度减1
            for (int j = 0; j < M; j++)
                if (table[i][j])
                    in[j]--;

            toposortDfs();
            //回溯
            ans.pop_back();
            in[i] = 0;
            for (int j = 0; j < M; j++)
                if (table[i][j])
                    in[j]++;
        }
    }
    return false;
}

int main()
{

    while (cin >> n >> m)
    {
        init();
        for (int i = 0; i < n; i++)
            cin >> map[i];
        initPos(); //确定边框的位置 左上和右下节点坐标
        initIn();  //构图

        cnt = 0;
        for (int i = 0; i < M; i++)
            if (exist[i])
                cnt++;

        toposortDfs();
    }
    return 0;
}