#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
string p2s(vector<int> const &v)
{
	string ret;
	int tot_left = 0;
	for (int i = 0; i < v.size(); ++i)
	{
		ret += ')';
		for (int j = 0; j < v[i] - tot_left; ++j)
		{
			ret.insert((ret.end() - 1), '(');
		}
		tot_left = v[i];
	}
	return ret;
}
vector<int> s2w(const string &s)
{
	vector<int> ret;
	typedef string::const_iterator It;
	It it = find(s.begin(), s.end(), ')');
	while (it != s.end())
	{
		It matched = it - 1;
		int interval = 0;
		while (true)
		{
			if (*matched == ')')
			{
				++interval;
				matched = (matched - 1);
			}
			else if (*matched == '(' && interval)
			{
				--interval;
				matched = (matched - 1);
			}
			else
			{
				break;
			}
		}
		ret.push_back(count(matched, (it + 1), ')'));
		it = find((it + 1), s.end(), ')');
	}
	return ret;
}
void p2w(int t)
{
	vector<int> v(t);
	for (int i = 0; i < t; ++i)
	{
		cin >> v[i];
	}
	vector<int> ans = s2w(p2s(v));
	for (int i = 0; i < ans.size(); ++i)
	{
		cout << ans[i] << ' ';
	}
	cout << '\n';
}
int main()
{
	int n;
	cin >> n;
	string p;
	int t;
	while (n--)
	{
		cin >> t;
		p2w(t);
	}
	return 0;
}
