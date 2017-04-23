//2299
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
int n;
struct Node
{
	int v;
	int rank;
};
bool operator<(Node const &n1, Node const &n2) { return n1.v < n2.v; }
#define LOWBIT(i) ((i)&(-(i)))
//查询之前缀和
int sum(int pos, int *bit)
{
	int ret = 0;
	while (pos > 0)
	{
		ret += bit[pos];
		pos -= LOWBIT(pos);
	}
	return ret;
}
//维护之加dif
void update(int pos, int dif, int *bit)
{
	while (pos <= n)
	{
		bit[pos] += dif;
		pos += LOWBIT(pos);
	}
}
int main()
{
#ifdef DEBUG
	freopen("C:\\Users\\admin\\Desktop\\编程\\in.txt", "r", stdin);
#endif

	while (scanf("%d", &n) && n)
	{
		Node *a = (Node *)malloc(n * sizeof(Node));
		for (int i = 0; i < n; ++i)
		{
			scanf("%d", &((a + i)->v));
			(a + i)->rank = i + 1;
		}
		//离散化discretization
		int *aa = (int *)malloc((n + 1) * sizeof(int));
		sort(a, a + n);
		for (int i = 0; i < n; ++i) aa[a[i].rank] = i + 1;
		int *bit = (int *)malloc((n + 1) * sizeof(int));
		memset(bit, 0, (n + 1) * sizeof(int));
		long long cnt = 0;
		for (int i = 1; i <= n; ++i)
		{
			update(aa[i], 1, bit);
			cnt += i - sum(aa[i], bit);
		}
		printf("%lld\n", cnt);
	}

#ifdef DEBUG
	freopen("con", "r", stdin);
	system("pause");
#endif // DEBUG
	return 0;

}
