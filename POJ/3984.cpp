#include <map>
#include <vector>
#include <iostream>
#include <queue>
using namespace std;
//POJ3984
int r[4] = { -1,0,1,0 };
int c[4] = { 0,-1,0,1 };
typedef pair<int, int> Axis;
struct Vector
{
	Axis pre;
	bool access;
	bool vst;
};
void print(vector<vector<Vector> > &v, Axis dest)
{
	if (dest.first == 0 && dest.second == 0)
	{
		cout << "(" << dest.first << ", " << dest.second << ")\n";
		return;
	}
	Axis p = v[dest.first][dest.second].pre;
	print(v, p);
	cout << "(" << dest.first << ", " << dest.second << ")\n";
}
int main()
{
	vector<vector<Vector> > v(5, vector<Vector>(5));
	int tmp;
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			v[i][j].vst = false;
			cin >> tmp;
			if (tmp == 1) v[i][j].access = false;
			else v[i][j].access = true;
		}
	}
	queue<Axis> q;
	Axis a(0, 0);
	q.push(a);
	v[a.first][a.second].vst = true;
	Axis ori;
	bool done = false;
	while (!done && !q.empty())
	{
		ori = q.front();
		q.pop();
		for (int i = 0; i < 4; ++i)
		{
			a = ori;
			a.first += r[i];
			a.second += c[i];
			if (a.first >= 0 && a.first < 5 && a.second >= 0 && a.second < 5 && v[a.first][a.second].access)
			{
				if (!v[a.first][a.second].vst)
				{
					v[a.first][a.second].vst = true;
					v[a.first][a.second].pre = ori;
//					cout << "cur (" << a.first << "," << a.second << ")'s pre is (" << ori.first << "," << ori.second << ")\n";
					if (a.first == 4 && a.second == 4)
					{
						done = true;
					}
					else
					{
						q.push(a);
					}
				}
			}
		}
	}
	print(v, make_pair<int, int>(4, 4));
//	system("pause");
	return 0;
}
