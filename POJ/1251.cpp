#include <iostream>
#include <vector>
using namespace std;
//POJ1251
int const INF = 0x3f3f3f3f;
int main()
{
	int n;
	while (cin >> n && n)
	{
		vector<vector<int> > g(n, vector<int>(n, INF));
		for (int i = 0; i < n; ++i)
		{
			g[i][i] = 0;
		}
		char c;
		int k;
		for (int i = 0; i < n - 1; ++i)
		{
			cin >> c >> k;
			int w;
			for (int j = 0; j < k; ++j)
			{
				cin >> c >> w;
				g[i][c - 'A'] = w;
				g[c - 'A'][i] = w;
			}
		}
		int sum = 0;
		vector<bool> vst(n, false);
		vector<int> closest(n);
		vst[0] = true;
		int pos = 0;
		for (int i = 1; i < n; ++i)
		{
			closest[i] = g[0][i];
		}
		for (int i = 0; i < n - 1; ++i)
		{
			int min = INF;
			for (int j = 0; j < n; ++j)
			{
				if (!vst[j] && closest[j] < min)
				{
					min = closest[j];
					pos = j;
				}
			}
			vst[pos] = true;
			sum += min;
			for (int j = 0; j < n; ++j)
			{
				if (!vst[j] && closest[j] > g[j][pos])
				{
					closest[j] = g[j][pos];
				}
			}
		}
		cout << sum << endl;
	}
//	system("pause");
	return 0;
}
