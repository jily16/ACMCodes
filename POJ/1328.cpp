#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
int n, d;
struct Island
{
	int x, y;
}iss[1001];
bool operator<(const Island &i1, const Island &i2) { return i1.x < i2.x; }
double get_radar(const Island &i) { return double(i.x) + sqrt(d*d - (i.y)*(i.y)); }
int main()
{
	int kase = 0;
	while (cin >> n >> d)
	{
		++kase;
		bool cannot = false;
		if (n == 0 && d == 0)
			break;
		else
		{
			for (int i = 0; i < n; ++i)
			{
				cin >> iss[i].x >> iss[i].y;
				if (iss[i].y > d || iss[i].y < 0)
				{
					cannot = true;
				}
			}
			if (cannot)
				cout << "Case " << kase << ": -1\n";
			else
			{
				int ans = 1;
				sort(iss, iss + n);
				double cur_radar = get_radar(iss[0]);
				//double tmp_radar;
				for (int i = 1; i < n; ++i)
				{
					if (iss[i].x < cur_radar && get_radar(iss[i]) < cur_radar)
					{
						cur_radar = get_radar(iss[i]);
						continue;
					}
					else if (iss[i].x <= cur_radar)
					{
						continue;
					}
					else if (iss[i].x > cur_radar && (iss[i].x - cur_radar)*(iss[i].x - cur_radar) + (iss[i].y)*(iss[i].y) <= d*d)
					{
						continue;
					}
					else
					{
						cur_radar = get_radar(iss[i]);
						++ans;
					}
				}
				cout << "Case " << kase << ": " << ans << "\n";
			}
		}
	}
	return 0;
}
