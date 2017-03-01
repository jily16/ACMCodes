#include <iostream>
using namespace std;
int main()
{
	int s, d;
	while (cin >> s >> d)
	{
		int surplus;
		double ratio = (double)s / (double)d;
		if (ratio < 0.25)
		{
			surplus = 10 * s - 2 * d;
		}
		else if (ratio < (2.0 / 3))
		{
			surplus = 8 * s - 4 * d;
		}
		else if (ratio < 1.5)
		{
			surplus = 6 * s - 6 * d;
		}
		else if (ratio < 4)
		{
			surplus = 3 * s - 9 * d;
		}
		else
		{
			surplus = -1;
		}
		if (surplus >= 0)
		{
			cout << surplus << "\n";
		}
		else
		{
			cout << "Deficit\n";
		}
	}
	return 0;
}
