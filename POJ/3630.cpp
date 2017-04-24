#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;
//3630
//MAXN有讲究，最大大不了就是单词数*长度，这是一个单词首尾相接的一维静态树
#define MAXN 100010
#define CHARSET 10
char const base = '0';
struct Trie
{
	int child[MAXN][CHARSET];	//树其实是一个一维数组交错跑的好多路线，第二维标记下一节点
	bool finish[MAXN];	//这一节点是否是单词结束
	int root;	//根是1，child[i][j]==0表示没有j方向的分支
	int tot;	//共多少节点在用
	Trie() :root(1), tot(1)
	{
		memset(child, 0, sizeof(child));
		for (int i = 0; i < MAXN; ++i) finish[i] = false;
	}
	//查短串前缀s存在
	bool find(char const *s)
	{
		int cur = root;
		for (char const *p = s; *p && cur; ++p) cur = child[cur][*p - base];
//		printf("Find %s ", s);
//		printf("%s\n", cur == 0 ? "failed" : "success");
		return cur != 0;	//s顺利跑完
		//查完整单词
		//return cur && finish[cur];	//s跑完 && 到树叶
	}
	void insert(char const *s)
	{
		int cur = root;
		for (char const *p = s; *p; ++p)
		{
			int &ref = child[cur][*p - base];
//			cout << "cur = " << cur << endl;
			if (!ref)
			{
//				cout << "child[" << cur << "][" << *p << "] now = " << tot + 1 << endl;
				ref = ++tot;
				cur = tot;
			}
			else cur = ref;
		}
		finish[cur] = true;
	}
};
bool cmp(char const *s1, char const *s2) { return strlen(s2) < strlen(s1); }
int main()
{
#ifdef DEBUG
	freopen("C:\\Users\\admin\\Desktop\\编程\\in.txt", "r", stdin);
#endif

	int t;
	scanf("%d", &t);
	while (t--)
	{
		int n;
		scanf("%d", &n);
		char **ss = (char **)malloc(n * sizeof(char *));
		for (int i = 0; i < n; ++i)
		{
			ss[i] = (char *)malloc(11);
			memset(ss[i], 0, 11);
		}
		Trie t;
		bool ok = true;
		for (int i = 0; i < n; ++i)
		{
			scanf("%s", ss[i]);
		}
		sort(ss, ss + n, cmp);
		for (int i = 0; i < n; ++i)
		{
//			puts(ss[i]);
			if (t.find(ss[i])) ok = false;
			else t.insert(ss[i]);
		}
		printf("%s\n", ok ? "YES" : "NO");
	}

#ifdef DEBUG
	freopen("con", "r", stdin);
	system("pause");
#endif // DEBUG
	return 0;

}
