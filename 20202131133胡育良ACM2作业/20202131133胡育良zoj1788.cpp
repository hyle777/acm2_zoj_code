//第八周 四分树
#include <iostream>
#include <string.h>
#include <queue>
using namespace std;

const int N = 522;

int map[N][N];

struct quadTree
{
    char val[3];
    quadTree *cld[4];
    quadTree()
    {
        strcpy(val, "");
        for (int i = 0; i < 4; i++)
            cld[i] = 0;
    }
    bool operator==(quadTree obj)
    {
        if (!strcmp(val, obj.val))
            return true;
        return false;
    }
};
quadTree *head;

quadTree *dfs_build(int r, int c, int len)
{
    quadTree *temp = new quadTree();
    if (len == 1)
    {
        temp->val[0] = '0';
        temp->val[1] = '0' + map[r][c];
        temp->val[2] = 0;
        return temp;
    }
    len /= 2;
    temp->cld[0] = dfs_build(r, c, len);
    temp->cld[1] = dfs_build(r, c + len, len);
    temp->cld[2] = dfs_build(r + len, c, len);
    temp->cld[3] = dfs_build(r + len, c + len, len);
    bool flag = true;
    for (int i = 1; i <= 3; i++)
        if (!(*temp->cld[0] == *temp->cld[i]))
        {
            flag = false;
            break;
        }
    if (flag)
    {
        strcpy(temp->val, temp->cld[0]->val);
        for (int i = 0; i < 4; i++)
        {
            delete temp->cld[i];
            temp->cld[i] = 0;
        }
    }
    else
        strcpy(temp->val, "1");
    return temp;
}

queue<quadTree *> qu;
char ans[N * N * 2];
void print()
{
    qu.push(head);
    strcpy(ans, "");
    while (!qu.empty())
    {
        quadTree *t = qu.front();
        qu.pop();
        strcat(ans, t->val);
        for (int i = 0; i < 4; i++)
        {
            if (t->cld[i] != 0)
                qu.push(t->cld[i]);
        }
    }

    //将字符串转化为16进制输出
    int len = 0;
    while (ans[len] != 0)
    {
        len++;
    }
    int fl = len % 4;
    int sum = 0;
    if (fl > 0)
    {
        for (int i = 0; i < fl; i++)
            sum = sum * 2 + (ans[i] - '0');
        printf("%0X", sum);
        sum = 0;
    }
    int k = 0;
    for (int i = fl; ans[i] != 0; i++)
    {
        sum = sum * 2 + (ans[i] - '0');
        k++;
        if (k % 4 == 0)
        {
            printf("%0X", sum);
            k = 0;
            sum = 0;
        }
    }
    printf("\n");
}

int main()
{
    int k;
    cin >> k;
    while (k--)
    {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> map[i][j];
        head = dfs_build(0, 0, n);
        print();
    }
    system("pause");
    return 0;
}