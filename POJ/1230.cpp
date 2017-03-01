#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Wall
{
	int row, l, r;
};
int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int n, k;
		cin >> n >> k;
		vector<Wall> walls(n);
		int _row, _l, _r;
		int min_col = 10000;
		int max_col = -1;
		for (int i = 0; i < n; ++i)
		{
			cin >> _l >> _row >> _r >> _row;
			if (_l < min_col) min_col = _l;
			if (_r > max_col) max_col = _r;
			if (_l > _r) swap(_l, _r);
			walls[i].l = _l;
			walls[i].r = _r;
			walls[i].row = _row;
		}
		int num = max_col + 1 - min_col;	//列数
		vector<int> cols(num, 0);
		for (int i = 0; i < n; ++i)
		{
			for (int j = walls[i].l; j <= walls[i].r; ++j)
			{
				++cols[j];
			}
		}
		vector<int> more(num);
		for (int i = 0; i < num; ++i)
		{
			more[i] = (cols[i] > k) ? (cols[i] - k) : 0;
		}
		vector<bool> dlt(n, false);
		int cnt = 0;
		for (int i = 0; i < num; ++i)
		{
			while (more[i] > 0)
			{
				++cnt;
				int most_over = -1;
				int to_dlt = -1;
				for (int j = 0; j < n; ++j)
				{
					if (!dlt[j] && walls[j].r >= i && walls[j].l <= i)
					{
						if (walls[j].r + 1 - i > most_over)
						{
							most_over = walls[j].r + 1 - i;
							to_dlt = j;
						}
					}
				}
				Wall dlt_wall = walls[to_dlt];
				for (int j = dlt_wall.l; j <= dlt_wall.r; ++j)
				{
					--more[j];
				}
				dlt[to_dlt] = true;
			}
		}
		cout << cnt << endl;
	}
	return 0;
}
