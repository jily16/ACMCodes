//1308
#include <cstdio>
#include <cstring>
using namespace std;
int const MAXN = 100;
int s[MAXN];
int f(int x)
{
	return s[x] == 0 ? x : s[x] = f(s[x]);
}
int main()
{
#ifdef DEBUG
	freopen("C:\\Users\\admin\\Desktop\\编程\\in.txt", "r", stdin);
#endif
	int x, y;
	int kase = 0;
	bool null = true;
	bool newtree = true;
	bool maybe = true;
	while (scanf("%d%d", &x, &y) != EOF)
	{
		if (x < 0 && y < 0) break;
		if (newtree)
		{
			memset(s, 0, MAXN * sizeof(int));
			null = true;
			newtree = false;
			printf("Case %d is ", ++kase);
		}
		if (null && x == 0 && y == 0)
		{
			printf("a tree.\n");
			newtree = true;
			continue;
		}
		if (x == 0 && y == 0)
		{
			//根唯一
			if (maybe)
			{
				int root = 0;
				int i = 1;
				for (; i < MAXN; ++i)
				{
					int fi = f(i);
//					if (i < 10) cout << "f(" << i << ")=" << fi << endl;
					if (fi && fi != i)
					{
						if(root == 0) root = fi;
						else if (root != fi)
						{
							maybe = false;
							break;
						}
					}
				}
			}
			if (maybe) printf("a tree.\n");
			else printf("not a tree.\n");
			maybe = true;
			newtree = true;
			continue;
		}
		null = false;
		if (maybe)
		{
			int fx = f(x);
			int fy = f(y);
//			cout << "Here" << endl;
			//单入
//			cout << "x="<<x<<", s[" << y << "]=" << s[y] << endl;
			if (s[y] && s[y] != x)
			{
				maybe = false;
				continue;
			}
			//无环
			else if (fx == fy && fx)
			{
				maybe = false;
				continue;
			}
//			cout << "Set " << x << "->" << y << endl;
			s[y] = x;
//			for (int i = 1; i < 10; ++i) cout << s[i] << " "; cout << endl;
		}
	}
#ifdef DEBUG
	freopen("con", "r", stdin);
	system("pause");
#endif // DEBUG
	return 0;
}
