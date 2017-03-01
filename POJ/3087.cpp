#include <iostream>
#include <string>

using namespace std;

int main()
{
	int n;
	cin >> n;
	for (int kase = 1; kase <= n; ++kase)
	{
		cout << kase << " ";
		int t;
		cin >> t;
		string a, b;
		cin >> a >> b;
		string c;
		cin >> c;
		string tmp = a + b;
		int time = 0;
		bool first = true;
		string ori_a = a, ori_b = b;
		while (tmp != c)
		{
			//cout << tmp << endl;
			if (tmp == ori_a + ori_b && !first)
			{
				time = -1;
				break;
			}
			a = tmp.substr(0, t);
			b = tmp.substr(t, t);
			tmp = a;
int wher = 0;
			for (int i = 0; i < b.size(); ++i)
			{
				tmp.insert(tmp.begin() + wher, b[i]);
				wher += 2;
			}
			++time;
			first = false;
		}
		cout << time << endl;
	}
	return 0;
}
