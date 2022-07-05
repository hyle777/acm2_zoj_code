#include<iostream>
using namespace std;
int main()
{
    int R[16], G[16], B[16];
    for (int i = 0; i < 16; i++)
        cin >> R[i] >> G[i] >> B[i];
    int r, g, b;  
    while (cin >> r >> g >> b)//输入 -1 -1 -1结束
    {
        if (r == -1 && g == -1 && b == -1) break;
        int minn = 0;
        int min = (R[0] - r) * (R[0] - r) + (G[0] - g) * (G[0] - g) + (B[0] - b) * (B[0] - b);
       for (int i = 0; i < 16; i++)
        {
           int t = (R[i] - r) * (R[i] - r) + (G[i] - g) * (G[i] - g) + (B[i] - b) * (B[i] - b);
           if (t < min) { min = t; minn = i; }
        }
       cout << "(" << r << "," << g << "," << b<<")" << " maps to " << "(" << R[minn] << "," << G[minn] << "," << B[minn] << ")";
       cout << endl;
    }
        return 0;
}