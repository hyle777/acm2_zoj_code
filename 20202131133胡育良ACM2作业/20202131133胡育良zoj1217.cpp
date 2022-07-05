//第六周 广度优先 散列
#include <iostream>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

string s;

string dest = "12345678x";
int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};
char dir[4] = {'u', 'l', 'r', 'd'};

// map 查找时间为O(logn) 超时
//改为unordered_map 哈希表 查找时间为O(1) 还是超时。。。
unordered_map<string, string> mp;
unordered_map<string, string>::iterator it;

queue<string> qu;

int main()
{
    char c;
    while (cin >> c)
    {
        s = "";
        mp.clear();
        s += c;
        for (int i = 0; i < 8; i++)
        {
            cin >> c;
            s += c;
        }
        queue<string> qu;
        qu.push(s);
        mp.insert({s, ""});
        int flag = 0;
        //广度优先bfs
        while (!qu.empty())
        {
            //取队头 判断
            //转化为4个状态 入队列
            // map存储状态
            string t = qu.front();
            qu.pop();
            it = mp.find(t);
            string road = it->second;
            if (t == dest)
            {
                flag = 1;
                cout << road << endl;
                break;
            }
            int p = 0;
            while (t[p] != 'x')
                p++;
            int px = p / 3, py = p % 3;
            for (int i = 0; i < 4; i++)
            {
                int nx = px + dx[i], ny = py + dy[i];

                if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3)
                {
                    int np = nx * 3 + ny;
                    swap(t[p], t[np]);
                    if (mp.find(t) == mp.end())
                    {
                        qu.push(t);
                        mp.insert({t, it->second + dir[i]});
                    }
                    swap(t[p], t[np]);
                }
            }
        }
        if (!flag)
            cout << "unsolvable" << endl;
    }
    system("pause");
    return 0;
}
