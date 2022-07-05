#include <iostream>
#include <queue>
#include <string.h>
using namespace std;

int d[8][8];

struct qunode
{
    int x;
    int y;
};
qunode destn;
queue<qunode> qu;
int bfs(qunode start)
{
    while (!qu.empty())
        qu.pop();
    qu.push(start);
    memset(d, -1, sizeof(d));
    d[start.x][start.y] = 0;
    while (!qu.empty())
    {
        qunode t = qu.front();
        qu.pop();
        if (t.x == destn.x && t.y == destn.y)
            return d[t.x][t.y];
        //状态转移 八个方向‘日’字形
        int dx[8] = {-1, -1, 1, 1, -2, -2, 2, 2};
        int dy[8] = {-2, 2, -2, 2, -1, 1, -1, 1};
        for (int i = 0; i < 8; i++)
        {
            qunode tt;
            tt.x = t.x + dx[i];
            tt.y = t.y + dy[i];
            if (tt.x >= 0 && tt.x < 8 && tt.y >= 0 && tt.y < 8 && d[tt.x][tt.y] == -1)
            {
                d[tt.x][tt.y] = d[t.x][t.y] + 1;
                qu.push(tt);
            }
        }
    }
}
int main()
{
    char c1;
    int x1;
    char c2;
    int x2;
    while (cin >> c1 && cin >> x1)
    {
        qunode start;
        start.x = c1 - 'a';
        start.y = x1 - 1;
        cin >> c2 >> x2;
        destn.x = c2 - 'a';
        destn.y = x2 - 1;
        cout << "To get from " << c1 << x1 << " to " << c2 << x2 << " takes " << bfs(start) << " knight moves." << endl;
    }
    return 0;
}