#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
const int maxn = 205;
struct node
{
    int x;
    int y;
    int ans;
};
char map[maxn][maxn];
int r, c, movex[4] = {1, -1, 0, 0}, movey[4] = {0, 0, -1, 1}, ans[maxn][maxn];
queue<node> q;
int main()
{
    while (scanf("%d%d", &r, &c) != EOF)
    {
        memset(ans, -1, sizeof(ans));
        for (int i = 0; i <= r + 1; i++)
            map[i][0] = map[i][c + 1] = '#';
        for (int i = 0; i <= c + 1; i++)
            map[0][i] = map[r + 1][i] = '#';
        int ex, ey;
        for (int i = 1; i <= r; i++)
        {
            getchar();
            for (int j = 1; j <= c; j++)
            {
                scanf("%c", &map[i][j]);
                if (map[i][j] == 'a')
                {
                    q.push((node){i, j, 0});
                }
                else if (map[i][j] == 'r')
                {
                    ex = i;
                    ey = j;
                }
            }
        }
        while (!q.empty())
        {
            node ita = q.front();
            q.pop();
            for (int i = 0; i < 4; i++)
            {
                int x = ita.x + movex[i];
                int y = ita.y + movey[i];
                if (map[x][y] == '#')
                    continue;
                if (ans[x][y] == -1 || ans[x][y] > ita.ans + 1)
                {
                    if (map[x][y] == 'x')
                    {
                        q.push((node){x, y, ita.ans + 2});
                        ans[x][y] = ita.ans + 2;
                    }
                    else
                    {
                        q.push((node){x, y, ita.ans + 1});
                        ans[x][y] = ita.ans + 1;
                    }
                }
            }
        }
        if (ans[ex][ey] == -1)
            printf("Poor ANGEL has to stay in the prison all his life.\n");
        else
            printf("%d\n", ans[ex][ey]);
    }
    return 0;
}