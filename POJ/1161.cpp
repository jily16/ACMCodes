//1161
#define MAXN 30000
int s[MAXN];
int f(int x)
{
	return s[x] == x ? x : s[x] = f(s[x]);
}
int main()
{
#ifdef DEBUG
	freopen("C:\\Users\\admin\\Desktop\\编程\\in.txt", "r", stdin);
#endif
	int m, n;
	while (scanf("%d%d", &n, &m) != EOF && (n || m))
	{
		for (int i = 0; i < MAXN; ++i)
		{
			s[i] = i;
		}
		if (m == 0)
		{
			printf("1\n");
			continue;
		}
		for (int i = 0; i < m; ++i)
		{
			int t;
			scanf("%d", &t);
			int grouproot = -1;
			int tmp;
			for (int j = 0; j < t; ++j)
			{
				scanf("%d", &tmp);
				int ft = f(tmp);
				if (grouproot == -1) grouproot = ft;
				else s[ft] = grouproot;
			}
		}
		int root = f(0);
		int cnt = 0;
		for (int i = 0; i < MAXN; ++i) if (f(i) == root) ++cnt;
		printf("%d\n", cnt);
	}
#ifdef DEBUG
	freopen("con", "r", stdin);
	system("pause");
#endif // DEBUG
	return 0;
}
