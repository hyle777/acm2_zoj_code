//第1周
#include <iostream>
using namespace std;

int main()
{
	double len;
	while (cin >> len && len != 0.0)
	{
		int i = 2;
		double sum = 0;
		while (sum < len)
		{
			sum += 1.0 / i;
			i++;
		}
		cout << i - 2 << " card(s)" << endl;
	}

	return 0;
}