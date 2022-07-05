//第2周
//将整数转化为二进制数 输出1的位置
#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int bin[100];
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        int len = 0;
        while (x)
        {
            bin[len++] = x % 2;
            x /= 2;
        }
        for (int j = 0; j < len; j++)
        {
            if (bin[j] == 1)
            {
                cout << j;
                if (j != len - 1)
                    cout << " ";
            }
        }
    }
    system("pause");
    return 0;
}