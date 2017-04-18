#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
#define M 100005
int s[M];
int e[M];	//enemy
int f(int x)
{
	return s[x] == x ? x : (s[x] = f(s[x]));
}
void u(int a, int b)
{
	int fa = f(a);
	int fb = f(b);
	if (fa != fb) s[fa] = fb;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t;
//	cin >> t;
	scanf("%d", &t);
	while (t--)
	{
		int n, m;
//		cin >> n >> m;
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i)
		{
			s[i] = i;
			e[i] = 0;
		}
		char op; int a, b;
		while (m--)
		{
//			cin >> op >> a >> b;
			char buf[5];
			scanf("%s%d%d", buf, &a, &b);
			op = buf[0];
			int fa = f(a);
			int fb = f(b);
			if (op == 'D')
			{
				if (e[a] == 0) { e[a] = fb; }
				if (e[b] == 0) { e[b] = fa; }
				u(a, e[b]);
				u(b, e[a]);
			}
			else
			{
//				if (fa == fb) { cout << "In the same gang." << endl; }
				if (fa == fb) { printf("In the same gang.\n"); }
//				else if (f(e[fa]) == fb) { cout << "In different gangs." << endl; }
				else if (f(e[fa]) == fb) { printf("In different gangs.\n"); }
//				else { cout << "Not sure yet." << endl; }
				else { printf("Not sure yet.\n"); }
			}
		}
	}
//	system("pause");
	return 0;
}
