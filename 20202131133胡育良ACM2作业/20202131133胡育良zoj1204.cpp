#include <iostream>
#include <string.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int d[40];
int m; //数组（集合）长度
vector<int> vec;
struct answer
{
    vector<int> v;
};
priority_queue<answer> heap;

bool operator<(const answer &a, const answer &obj)
{
    if (a.v.size() != obj.v.size())
        return a.v.size() > obj.v.size();
    return a.v > obj.v;
}
void dfs(int u, int sum)
{
    if (sum > d[m - 1])
        return;
    // if (sum == d[u])
    // {
    //     for (auto i : vec)
    //         cout << i << " ";
    //     cout << sum << endl;
    // }
    for (int i = u; i < m; i++)
    {
        if (sum == d[i])
        {
            // for (auto i : vec)
            //     cout << i << " ";
            // cout << sum << endl;
            vec.push_back(sum);
            heap.push({vec});
            vec.pop_back();
        }
        sum += d[i];
        vec.push_back(d[i]);
        dfs(i + 1, sum);
        //回溯
        vec.pop_back();
        sum -= d[i];
    }
}
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        memset(d, 0, sizeof(d));
        cin >> m;
        for (int i = 0; i < m; i++)
            cin >> d[i];
        sort(d, d + m);
        dfs(0, 0);

        if (heap.empty())
            cout << "Can't find any equations." << endl;
        else
            while (!heap.empty())
            {
                vector<int> t = heap.top().v;
                heap.pop();

                vector<int>::iterator it;
                it = t.begin();
                cout << *it;
                for (it = it + 1; it < t.end() - 1; it++)
                    cout << "+" << *it;
                cout << "=" << *it << endl;
            }
        cout << endl;
    }

    system("pause");
    return 0;
}
