#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;
int const INF = 0x3f3f3f3f;
//POJ 1502
//松弛边<u,v>
//d是点到源节点地距离
void relax(vector<vector<int> > const &g, vector<int> &d, int u, int v)
{
	if (d[v] > d[u] + g[u][v])
	{
		d[v] = d[u] + g[u][v];
	}
}
//Dijkstra算法
//边权非负
int dijkstra(vector<vector<int> > const &g, int s, int v)
{
	int n = g.size();
	vector<int> d(n);	//到源节点距离
	for (int i = 0; i < n; ++i)	//这是一步初始化
	{
		d[i] = g[s][i];
	}
	vector<bool> vst(n, false);
	int min_d = INF, min_d_pos = 0;
	while (min_d_pos != -1)
	{
		min_d_pos = -1;
		min_d = INF;
		for (int i = 0; i < n; ++i)	//找d最小的点
		{
			if (!vst[i] && d[i] < min_d)
			{
				min_d_pos = i;
				min_d = d[i];
			}
		}
		if (min_d_pos != -1)	//还有这样的边
		{
			vst[min_d_pos] = true;
			for (int i = 0; i < n; ++i)
			{
				if (g[min_d_pos][i] < INF)
				{
					relax(g, d, min_d_pos, i);
				}
			}
		}
	}
	return d[v];
}
int main()
{
	int n;
	while (cin >> n)
	{
		vector<vector<int> > g(n, vector<int>(n, INF));
		for (int i = 0; i < n; ++i) g[i][i] = 0;
		string s;
		for (int i = 1; i < n; ++i)
		{
			for (int j = 0; j < i; ++j)
			{
				cin >> s;
				if (s != "x")
				{
					g[i][j] = atoi(s.c_str());
					g[j][i] = atoi(s.c_str());
				}
			}
		}
		int ans = 0;
		for (int i = 0; i < n; ++i)
		{
			ans = max(ans, dijkstra(g, 0, i));
		}
		cout << ans << endl;
	}
//	system("pause");
	return 0;
}
