#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	double n, p;
	while (cin >> n >> p)
	{
		int k = pow(p, 1.0 / n) + 0.5;
		cout << k << endl;
	}
	return 0;
}
