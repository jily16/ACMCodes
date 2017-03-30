//导弹拦截
//动态规划
#include <vector>
#include <iostream>
using namespace std;

int dp(vector<int> &v)
{
	int n = v.size();
	vector<int> d(n, 1);
	vector<int> p(n, -1);	//parent
	for (int i = n - 2; i >= 0; --i)
	{
		for (int j = i + 1; j < n; ++j)
		{
			//不分开讨论要不要采取这个数必须采取
			if (v[i] >= v[j] && d[i] < d[j] + 1)
			{
				d[i] = d[j] + 1;
				p[i] = j;
			}
		}
	}
	int mx = -1;
	int pos = 0;
	for (int i = pos; i < n; ++i)
	{
		if (d[i] > mx)
		{
			mx = d[i];
			pos = i;
		}
	}
	//整理数组
	vector<int> del;
	int i = pos;
	while (p[i] != -1)
	{
		del.insert(del.begin(), i);
		i = p[i];
	}
	del.insert(del.begin(), i);
	for (i = 0; i < del.size(); ++i)
	{
		v.erase(v.begin() + del[i]);
	}
	return mx;
}
int main()
{
	//详细讨论:http://www.cnblogs.com/jily/p/6644934.html
	vector<int> v;
	int h;
	while (cin >> h) v.push_back(h);
	int i = 1;
	for (;; ++i)
	{
		int ans = dp(v);
		if (i == 1) cout << ans << endl;
		if (v.size() == 0) break;
	}
	cout << i << endl;
//	system("pause");
	return 0;
}
