#include <iostream>
using namespace std;

const int N = 100010;
int n, m;
int f[N];

int p[N];

int find(int x)
{
    if (p[x] != x)
        p[x] = find(p[x]);
    return p[x];
}
int Find(int x)
{
    if (p[x] < 0)
        return x;
    p[x] = Find(p[x]);
    return p[x];
}

int main()
{
    int k = 1;
    while (cin >> n >> m)
    {
        if (k != 1)
            cout << endl;
        cout << "Case " << k++ << ":" << endl;
        for (int i = 1; i <= n; i++)
        {
            // p[i] = i;
            p[i] = -1;
            f[i] = 1;
        }

        for (int i = 0; i < m; i++)
        {
            char c;
            cin >> c;
            if (c == 'M')
            {
                int a, b;
                cin >> a >> b;
                int fa = Find(a), fb = Find(b);
                if (fa != fb)
                {
                    // p[fa] = p[fb];
                    // f[fa] += f[fb];
                    // f[fb] = f[fa];
                    if (p[fa] < p[fb])
                    {
                        p[fa] += p[fb];
                        p[fb] = fa;
                    }
                    else
                    {
                        p[fb] += p[fa];
                        p[fa] = fb;
                    }
                }
            }
            else
            {
                int x;
                cin >> x;
                x = Find(x);

                // cout << f[x] << endl;
                cout << -p[x] << endl;
            }
        }
    }

    system("pause");
    return 0;
}