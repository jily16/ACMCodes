/*1182
#include <cstdio>
#define M 50005
#define POS_MOD3(x) (((x)+3)%3)
struct Animal
{
	int f;
	int r;	//0为同种1父吃子2子吃父
};
Animal s[M];
int f(int x)
{
	if (s[x].f != x)
	{
		int t = s[x].f;
		s[x].f = f(t);	//建立在对返回值的信任上，返回值是这一堆的根
		s[x].r = (s[t].r + s[x].r) % 3;	//精彩的递归
	}
	return s[x].f;
}
int main()
{
	freopen("C:\\Users\\admin\\Desktop\\编程\\in.txt", "r", stdin);
	int n, k;
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++i)
	{
		s[i].f = i;
		s[i].r = 0;
	}
	int d, x, y;
	int cnt = 0;
	while (k--)
	{
		scanf("%d%d%d", &d, &x, &y);
		if (x > n || y > n)
		{
			++cnt;
			continue;
		}
		int fx = f(x);
		int fy = f(y);
		if (d == 1)
		{
			if (fx == fy)
			{
				if (s[x].r != s[y].r)
				{
					++cnt;
				}
			}
			else
			{
				s[fy].f = fx;
				s[fy].r = (3 + s[x].r - s[y].r) % 3;
			}
		}
		else
		{
			if (fx == fy)
			{
				if ((s[x].r + 1) % 3 != s[y].r)
				{
					++cnt;
				}
			}
			else
			{
				s[fy].f = fx;
				s[fy].r = (4 + s[x].r - s[y].r) % 3;
			}
		}
	}
	printf("%d\n", cnt);
	freopen("con", "r", stdin);
//	system("pause");
	return 0;
}
