//3666
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define SET_ARRAY_0(a) (memset((a),0,(sizeof((a)))))
typedef long long LL;

struct DCT
{
	int v, id;
};
bool operator<(DCT const &d1, DCT const &d2) { return d1.v < d2.v; }
bool operator==(DCT const &d1, DCT const &d2) { return d1.v == d2.v; }	//unique中值相等就去重
int main()
{
#ifdef DEBUG
	freopen("C:\\Users\\admin\\Desktop\\编程\\in.txt", "r", stdin);
#endif

	int n;
	scanf("%d", &n);
	int *a = (int *)malloc(n * sizeof(int));
	SET_ARRAY_0(a);
	for (int i = 0; i < n; ++i) scanf("%d", a + i);
	//离散化副本b
	DCT *b = (DCT *)malloc(n * sizeof(DCT));
	for (int i = 0; i < n; ++i)
	{
		b[i].id = i;
		b[i].v = a[i];
	}
	sort(b, b + n);
	int dsize = unique(b, b + n) - b;
	//至此有了第i(0...dsize-1)小的数和值b[i].v的映射
	int **f = (int **)malloc(n * sizeof(int *));
	for (int i = 0; i < n; ++i) f[i] = (int *)malloc(dsize * sizeof(int));
	f[0][0] = abs(a[0] - b[0].v);
	for (int i = 1; i < dsize; ++i) f[0][i] = min(f[0][i - 1], abs(a[0] - b[i].v));
	for (int i = 1; i < n; ++i)
	{
		f[i][0] = f[i - 1][0] + abs(a[i] - b[0].v);
		for (int j = 1; j < dsize; ++j)
		{
			f[i][j] = min(f[i - 1][j] + abs(a[i] - b[j].v), f[i][j - 1]);
		}
	}
	int mn = INF;
	for (int i = 0; i < dsize; ++i) if (f[n - 1][i] < mn) mn = f[n - 1][i];
	////////////////////
	for (int i = 0; i < (n + 1) / 2; ++i) swap(a[i], a[n - 1 - i]);
	for (int i = 0; i < n; ++i)
	{
		b[i].id = i;
		b[i].v = a[i];
	}
	sort(b, b + n);
	dsize = unique(b, b + n) - b;
	//至此有了第i(0...dsize-1)小的数和值b[i].v的映射
	f[0][0] = abs(a[0] - b[0].v);
	for (int i = 1; i < dsize; ++i) f[0][i] = min(f[0][i - 1], abs(a[0] - b[i].v));
	for (int i = 1; i < n; ++i)
	{
		f[i][0] = f[i - 1][0] + abs(a[i] - b[0].v);
		for (int j = 1; j < dsize; ++j)
		{
			f[i][j] = min(f[i - 1][j] + abs(a[i] - b[j].v), f[i][j - 1]);
		}
	}
	for (int i = 0; i < dsize; ++i) if (f[n - 1][i] < mn) mn = f[n - 1][i];
	printf("%d\n", mn);


#ifdef DEBUG
	freopen("con", "r", stdin);
	system("pause");
#endif // DEBUG
	return 0;

}
