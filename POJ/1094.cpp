#include <vector>
#include <iostream>
#include <queue>
using namespace std;
int const INF = 0x3f3f3f3f;
//POJ1094
//返回空数组说明暂时不行
//cyclic说明矛盾
vector<int> ts(vector<vector<int> > const &g, bool &cyclic)
{
	int n = g.size();
	vector<int> d(n);
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (g[i][j] < INF)
			{
				++d[j];
		//		cout << i << "<" << j << ",d[" << j << "]=" << d[j] << endl;
			}
		}
	}
	for (int i = 0; i < n; ++i)
	{
	//	cout << d[i] << ",";
	}
	queue<int> q;
	for (int i = 0; i < n; ++i) if (d[i] == 0) q.push(i);
	int d0;
	int tot = 0;
	bool not_unique = false;
	vector<int> ans;
	while (!q.empty())
	{
		if (q.size() > 1)
		{
//			cout << "Here not unique" << endl;
//			while (!q.empty()) { cout << (char)(q.front() + 'A'); q.pop(); }
			not_unique = true;
		}
		d0 = q.front();
		q.pop();
		ans.push_back(d0);
//		cout << (char)('A' + d0);
		++tot;
		for (int i = 0; i < n; ++i)
		{
			if (d[i] != 0 && g[d0][i] < INF)
			{
				--d[i];
				if (d[i] == 0)
				{
					q.push(i);
				}
			}
		}
	}
//	cout << endl;
	if (tot != n) cyclic = true;
	if (not_unique) return vector<int>();
	else return ans;
}
int main()
{
	int n, m;
	while (cin >> n >> m && n && m)
	{
		bool done = false;
		vector<vector<int> > g;
		char alp1, alp2;
		char lessthan;
		int num1, num2;
		for (int i = 0; i < m; ++i)
		{
			cin >> alp1 >> lessthan >> alp2;
			if (done) continue;
			num1 = alp1 - 'A';
			num2 = alp2 - 'A';
			int bignum = max(num1, num2);
			//extend the graph
			if (g.size() < bignum + 1)
			{
				int ori_size = g.size();
				for (int i = 0; i < ori_size; ++i)
				{
					for (int j = 0; j < bignum + 1 - ori_size; ++j)
					{
						g[i].push_back(INF);
					}
				}
				for (int i = 0; i < bignum + 1 - ori_size; ++i)
				{
					g.push_back(vector<int>(bignum + 1, INF));
				}
			}
			g[num1][num2] = 1;
			//judge from here
			bool cycle = false;
			if (g.size() < n)
			{
				ts(g, cycle);
				if (cycle)
				{
					cout << "Inconsistency found after " << i + 1 << " relations.\n";
					done = true;
				}
				else
				{
					if (i == m - 1)
					{
						cout << "Sorted sequence cannot be determined.\n";
						done = true;
					}
				}
			}
			else
			{
				vector<int> ans = ts(g, cycle);
				if (cycle)
				{
					cout << "Inconsistency found after " << i + 1 << " relations.\n";
					done = true;
				}
				else
				{
					if (ans.size() != 0)
					{
							cout << "Sorted sequence determined after " << i + 1 << " relations: ";
							for (int i = 0; i < n; ++i) cout << (char)(ans[i] + 'A');
							cout << ".\n";
							done = true;
					}
					else
					{
						if (i < m - 1) continue;
						else
						{
							cout << "Sorted sequence cannot be determined.\n";
							done = true;
						}
					}
				}
			}
		}
	}
	return 0;
}
