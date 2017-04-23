#include <string>
#include <algorithm>
#include <iostream>
using namespace std;
#define MAXN 101
long long const INF = 0x3f3f3f3f;
struct Node
{
	char key;
	int w, f, l, r;
	Node() :w(0), f(-1), l(-1), r(-1) {}
};
//tree[2 * k - 1]是树根
void build(Node *tree, int n)	//k字符种类数目
{
	for (int i = 0; i < 2 * n - 1; ++i) tree[i].f = tree[i].l = tree[i].r = -1;
	for (int i = n; i < 2 * n - 1; ++i)
	{
		int lnode = -1, rnode = -1;
		int lmax = INF, rmax = INF;
		for (int j = 0; j < i; ++j)
		{
			if (tree[j].f == -1)
			{
				if (tree[j].w < lmax)
				{
					rmax = lmax;
					rnode = lnode;
					lmax = tree[j].w;
					lnode = j;
				}
				else if (tree[j].w < rmax)
				{
					rmax = tree[j].w;
					rnode = j;
				}
			}
		}
		tree[i].w = tree[lnode].w + tree[rnode].w;
		tree[i].l = lnode;
		tree[i].r = rnode;
		tree[lnode].f = tree[rnode].f = i;
	}
}
void gencode(Node *tree, string *cd, int index)
{
	if (tree[index].f == -1 && tree[index].l == -1 && tree[index].r == -1)  cd[index] = "0";
	else if (tree[index].f != -1)
	{
		cd[index] = cd[tree[index].f];
		if (index == tree[tree[index].f].l) cd[index].insert(cd[index].begin(), '0');
		else cd[index].insert(cd[index].begin(), '1');
	}
	if (tree[index].l != -1) gencode(tree, cd, tree[index].l);
	if (tree[index].r != -1) gencode(tree, cd, tree[index].r);
}
int main()
{
#ifdef DEBUG
	freopen("C:\\Users\\admin\\Desktop\\编程\\in.txt", "r", stdin);
#endif


	string s;
	while (cin >> s &&s != "END")
	{
		int n = 0;
		Node tree[MAXN];
		string cd[MAXN];
		sort(s.begin(), s.end());
		tree[0].key = s[0];
		tree[0].w = 1;
		int cnt = 1;
		for (int i = 1; i < s.size(); ++i)
		{
			if (s[i] == s[i - 1]) ++cnt;
			else
			{
				tree[n++].w = cnt;
				tree[n].key = s[i];
				cnt = 1;
			}
		}
		tree[n++].w = cnt;
		build(tree, n);
//		huffmancode(tree, cd, n, len);
		gencode(tree, cd, 2 * n - 2);
		int wpl = 0;
		for (int i = 0; i < n; ++i)
		{
			wpl += cd[i].size()*tree[i].w;
		}
		printf("%d %d %.1lf\n", 8 * s.size(), wpl, 8.0*s.size() / wpl);
	}

#ifdef DEBUG
	freopen("con", "r", stdin);
	system("pause");
#endif // DEBUG
	return 0;
}
