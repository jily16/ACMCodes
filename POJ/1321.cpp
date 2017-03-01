#include <iostream>
using namespace std;
int n, kk;
int f(char **a, int lines, int *q, int k)
{
	//一个数组，q[i]表示第i行的棋子放在哪一列
	if (k > lines) return 0;
	if (k == 0) return 1;
	if (lines == 1)
	{
		int ans = 0;
		for (int i = 0; i < n; ++i)
		{
			if (a[0][i] == '#')
			{
				bool never = true;
				for (int j = 0; j < n - lines; ++j)
				{
					if (q[j] == i)
					{
						never = false;;
					}
				}
				if (never)
					++ans;
			}
		}
		return ans;
	}
	else
	{
		int ans = 0;
		//不放
		q[n - lines] = -1;
		ans += f(a + 1, lines - 1, q, k);
		//放
		for (int i = 0; i < n; ++i)
		{
			if (a[0][i] == '#')
			{
				bool never = true;
				for (int j = 0; j < n - lines; ++j)
				{
					if (q[j] == i)
					{
						never = false;;
					}
				}
				if (never)
				{
					q[n - lines] = i;
					ans += f(a + 1, lines - 1, q, k - 1);
				}
			}
		}
		return ans;
	}
}
int main()
{
	while (cin >> n >> kk)
	{
		if (n == -1 && kk == -1)
			break;
		else
		{
			char **v = (char **)new(char *[n]);
			for (int i = 0; i < n; ++i)
			{
				v[i] = (char *)new(char[n]);
			}
			for (int i = 0; i < n; ++i)
			{
				for (int j = 0; j < n; ++j)
				{
					cin >> v[i][j];
				}
			}
			int *q = (int *)new(int[n]);
			cout << f(v, n, q, kk) << endl;
			for (int i = 0; i < n; ++i)
			{
				delete[] v[i];
			}
			delete[] v;
		}
	}
	return 0;
}
