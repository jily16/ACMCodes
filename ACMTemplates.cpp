/**************************************
**	author:jily
**	update:4/28/2017
**************************************/

/**************************************
**	<<<<Tips>>>>
**
**	nonincreasing/nondecreasing非递增/非递减--->非严格单调11334非递减
**	单调区间求一个数使∑|ai-num|最小那么num是中位数
**
**************************************/

#include <queue>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//#define INT64_MAX        9223372036854775807
//#define INT32_MAX        2147483647
#define INF 0x3f3f3f3f	//神奇的无穷大
#define MAXN 10010

#define SET_ARRAY_0(a) (memset((a),0,(sizeof((a)))))

namespace ufs
{
	//基本实现
	namespace base
	{
		int s[MAXN];
		int rank[MAXN];

		int n;	//实际尺寸
		void init()
		{
			for (int i = 0; i < n; ++i) s[i] = i;
			for (int i = 0; i < n; ++i) rank[i] = 1;	//按秩合并
		}

		int f(int x)
		{
			while (x != s[x]) x = s[x];	//迭代求法
			return x;
		}

		//一种路径压缩的做法
		//路径压缩会把路径清空所以注意保存关系慎用
		//下面的种类并查集就是用的路径压缩并保存了关系
		//不要求路径的话路径压缩好处多多
		int f2(int x)
		{
			return s[x] == x ? x : s[x] = f2(s[x]);
		}

		//按秩合并
		void u(int x, int y)
		{
			if (f(x) == f(y)) return;	//不合并已在一组的是有道理的
			if (rank[x] > rank[y]) s[f(y)] = x;	//始终应更新根节点或者叫代表节点
			else if (rank[x] == rank[y])
			{
				s[f(x)] = y;
				++rank[y];
			}
			else s[f(x)] = y;
		}
	}

	//结构的ufs可以维护节点之间的相对关系
	//名曰种类并查集
	struct Node
	{
		int f;	//父节点
				//查询时总是更新为一个堆的根节点
		int r;	//与父节点的关系
				//也就总是可以方便获得与根的关系确定其在堆里面的相对状态
	}s[MAXN];
	int f(int x)
	{
		if (s[x].f != x)	//维护和根节点的关联同时维护和根节点相对关系
		{
			int tmp = s[x].f;
			s[x].f = f(tmp);	//建立在对返回值的信任上，返回值是这一堆的根，路径压缩无妨
			s[x].r = (s[tmp].r + s[x].r) % 3;	//举例POJ1182的一个归纳关系
												//s[x].r是x到tmp的关系and s[tmp].r是递归已经维护好的tmp到根的关系
		}
	}
	int u(int a, int b)
	{
		//由于前面好的维护，这里只要从两组a(b)->root的关系中找到规律写了就好
		//把哪一坨接到另一坨都有可能是讲究的要好好找规律
	}
}

namespace graph
{
	int g[MAXN][MAXN];

	//拓扑排序torpological_sort
	//Directed Acyclic Graph(DAG)
	//返回true说明没有死锁
	namespace torpological
	{
		bool ts()
		{
			int n;	//图的实际尺寸
			int *d = (int *)malloc(n * sizeof(int));	//入度数组
			queue<int> q;	//0入度顶点集合
			while (!q.empty()) q.pop();
			for (int i = 0; i < n; ++i)
			{
				for (int j = 0; j < n; ++j)
				{
					if (g[i][j] < INF)
					{
						++d[j];
					}
				}
			}
			for (int i = 0; i < n; ++i) if (d[i] == 0) q.push(i);
			int d0;
			int total_out = 0;
			while (!q.empty())
			{
				//这里检查q的大小可以判断路径是否唯一
				d0 = q.front();
				q.pop();
				++total_out;
				//			cout << d0 << endl;	//或其他和顺序有关的操作
				for (int i = 0; i < n; ++i)
				{
					if (d[i] != 0 && g[d0][i] < INF)
					{
						--d[i];
						if (d[i] == 0) q.push(i);
					}
				}
			}
			return total_out == n;
		}
	}

	//最小生成树(全径权值)
	namespace mst
	{
		//Prim算法
		//模板题POJ1251
		//感谢博主http://www.cnblogs.com/Veegin/archive/2011/04/29/2032388.html提供优秀的做法
		int prim()
		{
			int n;	//尺寸
			int sum = 0;
			bool *vst = (bool *)malloc(n * sizeof(bool));
			for (int i = 0; i < n; ++i) vst[i] = false;	//visited就是已经在树上
			int *closest = (int *)malloc(n * sizeof(int));
			vst[0] = true;
			int pos = 0;
			for (int i = 1; i < n; ++i)
			{
				closest[i] = g[0][i];	//初始化距离数组
										//不采用算导的key成员做法而是单开数组毕竟方便好写
			}
			for (int i = 0; i < n - 1; ++i)
			{
				int min = INF;
				for (int j = 0; j < n; ++j)
				{
					if (!vst[j] && closest[j] < min)
					{
						min = closest[j];
						pos = j;
					}
				}
				vst[pos] = true;	//手动查找最近点pos
									//可以考虑一下priority_queue怎么写可以提速反正现在懒得写...
									//算导的斐波那契堆提速他自己也说了是一种理论的追求那算了吧
				sum += min;	//增加总权值作为结果
							//如果需要树的话这个地方应该有其他操作
				for (int j = 0; j < n; ++j)
				{
					if (!vst[j] && closest[j] > g[j][pos])
					{
						closest[j] = g[j][pos];	//点上树后更新树下的点
					}
				}
			}
			return sum;
		}

		//Kruskal算法求最小生成树
		//与Prim不同
		//Kruskal维护多个一开始为单节点树的子图并逐渐合并
		struct KruskalEdge	//支持权重排序的边
		{
			int v1, v2;
			int weight;
			KruskalEdge(int _v1, int _v2, int w) :v1(_v1), v2(_v2), weight(w) {}
		};
		bool operator<(KruskalEdge const &e1, KruskalEdge const &e2) { return e1.weight > e2.weight; }
		int kruskal(vector<vector<int> > const &g)
		{
			int n;
			//		int *ufs = (int *)malloc(n * sizeof(int));	//并查集
			//		vector<int> rank(n);
			ufs::base::init();
			priority_queue<KruskalEdge> pq;	//非降序排序边
			while (!pq.empty()) pq.pop();
			for (int i = 0; i < n; ++i)
			{
				for (int j = 0; j < n; ++j)
				{
					if (g[i][j] < INF)
					{
						pq.push(KruskalEdge(i, j, g[i][j]));
					}
				}
			}
			//下面开始处理
			//要整棵生成树的话要维护一个π属性的前驱子图
			//为简化我这里只要一个总权值
			int sum = 0;
			while (!pq.empty())
			{
				KruskalEdge e = pq.top();	//每次找出轻量级边并入子图
				pq.pop();
				if (ufs::base::f(e.v1) != ufs::base::f(e.v2))	//在某一分量之内则忽略
				{
					sum += e.weight;
					//其他操作
					ufs::base::u(e.v1, e.v2);	//加入分量
				}
			}
			return sum;
		}
	}

	//最短路径问题
	namespace sp
	{
		//松弛边<u,v>
		//Dijkstra和Bellman-Ford的共同必要操作
		//d是点到源节点地距离
		int d[MAXN];
		void relax(int u, int v)
		{
			if (d[v] > d[u] + g[u][v])
			{
				d[v] = d[u] + g[u][v];
				//如果有前驱子图要维护的话就应该在这
			}
		}

		//Dijkstra算法
		//边权非负的有向图的最短路径
		int dijkstra(int s, int v)
		{
			int n;
			for (int i = 0; i < n; ++i)	//这是一步初始化
			{
				d[i] = g[s][i];
			}
			bool *vst = (bool *)malloc(n * sizeof(bool));
			for (int i = 0; i < n; ++i) vst[i] = false;
			int min_d = INF, min_d_pos = 0;
			while (min_d_pos != -1)
			{
				min_d_pos = -1;
				min_d = INF;
				for (int i = 0; i < n; ++i)	//找d最小的点
				{
					if (!vst[i] && d[i] < min_d)
					{
						min_d_pos = i;
						min_d = d[i];
					}
				}
				if (min_d_pos != -1)	//还有要松弛的边
				{
					vst[min_d_pos] = true;
					for (int i = 0; i < n; ++i)
					{
						if (g[min_d_pos][i] < INF)
						{
							relax(min_d_pos, i);
						}
					}
				}
			}
			return d[v];
		}

		//Bellman-Ford算法
		//计算可含负权值的有向图的单源最短路径并检测负权环
		//返回true代表有可行解
		//false表示有负环
		//因为要返回bool值所以路径结果只能体现在引用参数值中
		bool bellman_ford(int s)
		{
			int n;
			for (int i = 0; i < n; ++i)	//初始化d数组
			{
				d[i] = g[s][i];
			}
			for (int i = 0; i < n - 1; ++i)	//核心对所有边进行n-1次松弛
			{
				for (int j = 0; j < n; ++j)
					for (int k = 0; k < n; ++k)
					{
						if (g[j][k] < INF)	//有边
						{
							relax(j, k);
						}
					}
			}	//至此已经完成d数组的全部松弛工作
				//下面判负权环
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < n; ++j)
				{
					if (g[i][j] < INF)	//是边
					{
						if (d[j] > d[i] + g[i][j])
						{
							return false;
						}
					}
				}
			return true;
		}
	}

	//欧拉路

	//连通性

	//二分图的最大匹配

	//最大流的增广路KM算法

	//最小费用最大流

	//有上下界的网络流

	//差分约束系统

	//双连通分量

	//强连通分支及其缩点

	//割边和割点

	//最小割模型和网络流规约

	//度限制最小生成树

	//第k最短路

	//最优比率生成树

	//最小树形图

	//次小生成树

	//有/无向图最小环
}

namespace tree
{
	//Huffman树
	//最优二叉树
	//判定过程最优
	//带权路径长度WPL(∑(叶子权*深度))最小
	//不一定结果一定是全往一边偏那种--->主要看自下向上合并的树长什么样
	namespace huffman
	{
		//用2*n-1数组表示的哈夫曼树的节点
		struct Node
		{
			char key;
			int w, f, l, r;	//weight,father,left,right
			Node() :w(0), f(-1), l(-1), r(-1) {}
		};
		//tree[2 * n - 2]是树根
		//此时传进来的数组只是读入数据之后的形态，[0,n-1]有key，w，其他信息都没有(最终都是叶子)，这里处理
		void build(Node *tree, int n)	//k字符种类数目
		{
			for (int i = 0; i < 2 * n - 1; ++i) tree[i].f = tree[i].l = tree[i].r = -1;
			//建树过程
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

		//根据树生成哈夫曼编码
		//每个实在的存key的节点都是叶子
		//通过调gencode(tree, cd, 2 * n - 2);来递归
		void gencode(Node *tree, std::string *cd, int index)
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
	}

	//二叉搜索树
	//静态
	//动态

	//线段树
	//http://www.cnblogs.com/wuyiqi/archive/2012/03/19/2405885.html
	//http://blog.csdn.net/metalseed/article/details/8039326
	namespace segment_tree
	{
		//基础线段树
		namespace base
		{
			int tree[4 * MAXN + 10];	//数组元素不一定是int，也可能是信息更多的结构，下标从1开始
			int a[MAXN];	//存数据，下标起点随意吧从0开始OK
			void build(int i, int al, int ar)	//以tree[i]为根建[a[al],a[ar]]范围的树
			{
				if (al == ar) { tree[i] = a[ar]; return; }
				int m = (al + ar) >> 1;
				int lc = i << 1;	//i<<1+1======>i<<2坑爹的优先级
				build(lc, al, m);
				build(lc + 1, m + 1, ar);
				//回溯由tree[lc]和tree[lc+1]得到tree[i]信息
				//比如维护区间最小值
				tree[i] = min(tree[lc], tree[lc + 1]);
			}
			int query(int i, int al, int ar, int ql, int qr)
			{
				//树以tree[i]为根，维护了[a[al],a[ar]]范围
				//在这个范围中查找维护的区间[a[ql],a[qr]]
				//query(1,start,len(a)-1+start,ql,qr);
				if (al > qr || ar < ql) return -1;
				if (al >= ql && ar <= qr) return tree[i];
				int lc = i << 1;
				int am = (al + ar) >> 1;
				int q1 = query(lc, al, am, ql, qr);
				int q2 = query(lc + 1, am + 1, ar, ql, qr);
				if (q1 == -1) return q2;	//一边没查询到
				if (q2 == -1) return q1;
				//两个后代都查询到综合结果，比如维护最小
				return min(q1, q2);
			}
			/*
			线段树的父子关系和<<<<管辖>>>>区间的折半关系是对应的
			*/
			//单点更新
			void update(int i, int al, int ar, int id, int v)
			{
				if (al == ar) { tree[i] = v; return; }
				int am = (al + ar) >> 1;
				int lc = i << 1;
				//递归更新
				if (id <= am) update(lc, al, am, id, v);
				else update(lc + 1, am + 1, ar, id, v);
				//维护树
				tree[i] = min(tree[lc], tree[lc + 1]);
			}
			//区间更新
			//对[a[ul],a[ur]]区间执行不可描述之操作
			//lazy思想，需要一个额外的数组[2*MAXN+10]来暂存父节点的操作(选好方式)，当需要查子节点的时候再pushdown
			void pushdown(int i);
			void pushup(int i);	//i的孩子节点已经更新，更新i----->tree[i]=foo(tree[lc],tree[lc+1]);
			void update(int i, int al, int ar, int ul, int ur)	//签名和单点更新一样，其实这个情况不该出现
			{
				if (ul <= al && ur >= ar) {/*modify and mark*/ return; }
				pushdown(i);
				int am = (al + ar) >> 1;
				if (ul <= am) update(i << 1, al, am, ul, ur);	//ul和ur总是ul和ur可不敢自作聪明乱改了...
				if (ur >= am + 1) update(i << 1 | 1, am + 1, ar, ul, ur);
				pushup(i);
			}
			int query(int i, int al, int ar, int ql, int qr)
			{
				//if(marked(i)) pushdown(i);
				//哎呀理解之后好简单不写了。。。
			}
		}

		//可持久化线段树/函数式线段树/主席树
		//http://www.cnblogs.com/zinthos/p/3899565.html
		//http://www.cnblogs.com/tedzhao/archive/2008/11/12/1332112.html
	}

	//区间树

	//树状数组(binary indexed tree)
	//区间和的维护(数组前缀和)
	//https://www.topcoder.com/community/data-science/data-science-tutorials/binary-indexed-trees/#prob
	//重点!!!BIT维护的是<<<<cumulative frequency table>>>>是区间的frequency频数!!!!!
	//树状数组，as well as线段树，数组长度是数据范围，当压力很大时要离散化也就是下面discretization的事情
	namespace bit
	{
		//一维
		namespace d1
		{
			//a[1...MAXN]存原始数据
			int a[MAXN + 1];
			//bit是树
			int bit[MAXN + 1];

			//这个名字意思是返回值是右起第一个1代表的数
			//这个函数返回的是bit[i]代表之前(含自己)几个数的和，也是它加几得到父节点反正挺重要的数
			//干脆写成宏
			//和#define LOWBIT(i) ((i)&((i)^((i)-1)))居然一样
#define LOWBIT(i) ((i)&(-(i)))

			//查询之前缀和
			int sum(int pos)	//下标从1开始记!
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
			void update(int pos, int dif)
			{
				while (pos <= MAXN)
				{
					bit[pos] += dif;
					pos += LOWBIT(pos);
				}
			}

			void init() { for (int i = 1; i < MAXN; ++i) update(i, a[i]); }
		}

		//二维
		namespace d2
		{

		}
	}

	//离散化
	namespace discretization
	{
		struct DCT
		{
			int v, id;
		};
		bool operator<(DCT const &d1, DCT const &d2) { return d1.v < d2.v; }
		bool operator==(DCT const &d1, DCT const &d2) { return d1.v == d2.v; }	//unique中值相等就去重
		int a[MAXN];
		DCT b[MAXN];
		void fu_ktion()
		{
			for (int i = 0; i < MAXN; ++i)
			{
				b[i].id = i;
				b[i].v = a[i];
			}
			std::sort(b, b + MAXN);
			int dsize = std::unique(b, b + MAXN) - b;
			//至此有了第i(0...dsize-1)小的数和值b[i].v的映射
		}
	}

	//树链剖分

	//trie树
	namespace trie
	{
		//MAXNODE有讲究，最大大不了就是单词数*长度，这是一个单词首尾相接的一维静态树
		int const MAXNODE = 100010;
		int const CHARSET = 10;
		char const base = '0';
		/*一维树大概长这个样子
		1---(j)--->2---(i)--->3---(l)--->4---(y)--->5
		           |
				  (l)
				   |
				   6---(y)--->7
		*/
		struct Trie
		{
			int child[MAXNODE][CHARSET];	//树其实是一个一维数组交错跑的好多路线，第二维标记下一节点
			bool finish[MAXNODE];	//这一节点是否是单词结束
			int root;	//根是1，child[i][j]==0表示没有j方向的分支
			int tot;	//共多少节点在用
			Trie() :root(1), tot(1)
			{
//				memset(child, 0, sizeof(child));
				SET_ARRAY_0(child);
				for (int i = 0; i < MAXNODE; ++i) finish[i] = false;
			}
			//查短串前缀s存在
			//理清楚是插长查短还是插短查长
			bool find(char const *s)
			{
				int cur = root;
				for (char const *p = s; *p && cur; ++p) cur = child[cur][*p - base];
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
					if (!ref)
					{
						ref = ++tot;
						cur = tot;
					}
					else cur = ref;
				}
				finish[cur] = true;
			}
		};
	}

	//堆


	//AVL树

	//左偏树
	//可合并堆
	namespace leftist_tree	//mergeable heap
	{
		//定义bool operator<(T const &t1, T const &t2)的类型
		//和std::priority_queue接口尽量一致(大根堆)
		template<T>
		struct LeftishTree
		{
			int tot;	//共用多少个节点已经
			T v[MAXN];	//一维静态树
			int dis[MAXN];
			int l[MAXN];
			int r[MAXN];
			LeftishTree() :tot(0)
			{
				SET_ARRAY_0(v);
				SET_ARRAY_0(dis);
				SET_ARRAY_0(l);
				SET_ARRAY_0(r);
			}
			int merge(int a, int b)
			{
				if (!a) return b;
				if (!b) return a;
				if (v[a] < v[b]) swap(a, b);
				r[a] = merge(r[a], b);
				if (dis[l[a]] < dis[r[a]]) swap(l[a], r[a]);
				dis[a] = dis[r[a]] + 1;
				return a;
			}
			int init(T w)	//返回新树的根
			{
				++tot;
				v[tot] = w;
				l[tot] = r[tot] = dis[tot] = 0;
				return tot;
			}
			int insert(int x, T w)	//向x树插入权重w的点返回这棵树的新根
			{
				return merge(x, init(w));
			}
			T top(int x) { return v[x]; }	//树根自然是top	//返回0空树
			int pop(int x) { return merge(l[x], r[x]); }	//返回0说明树pop空了
			//int size() { return tot; }	//tot对外是没有价值的，pop不会缩tot
		};
	}

	//前缀树

	//后缀树

	//平衡树
	namespace balanced_tree
	{
		//treap

		//splay树
		//动态树CLT问题
	}
}

namespace rmq
{
	//RMQ算法

	//ST表

	//LCA和RMQ
	//离线算法并查集+dfs
	//在线算法RMQ+dfs
}

namespace dp
{
	//背包问题

	//最长公共子序列

	//最优二分检索树

	//树形dp

	//双端队列优化状态转移

	//数位dp
}

namespace matrix
{
	/*
	矩阵Size:Row*Col
	快速幂中矩阵为方阵
	*/
	const int Row = 3;
	const int Col = 3;
	const int mod = 1e9 + 7;
	typedef struct Matrix
	{
		long long m[Row][Col];
	} Matrix;
	Matrix operator * ( Matrix a, Matrix b ) //通用矩阵乘法
	{
		Matrix res;
		for ( int i = 0; i < Row; i++ )
		{
			for ( int j = 0; j < Col; j++ )
			{
				res.m[i][j] = 0;
				for ( int k = 0; k < Row ; k++ )
				{
					res.m[i][j] += a.m[i][k] * b.m[k][j];
					res.m[i][j] %= mod;
				}
			}
		}
		return res;
	}
	Matrix fast_power ( Matrix a, long long n )
	{
		Matrix res;
		memset ( res.m, 0, sizeof ( res.m ) );
		for ( int i = 0; i < Row; i++ ) //构造单位矩阵，单位矩阵必为方阵所以取Row;
			res.m[i][i] = 1;
		if ( n == 1 )
			return a;
		while ( n )
		{
			if ( n & 1 ) // n为奇数
			{
				res = res * a;
			}
			n >>= 1;
			a = a * a;
		}
		return res;
	}
}

namespace string
{
	//KMP算法
	//http://www.cnblogs.com/jackge/archive/2013/01/05/2846006.html
	int next[MAXN];
	std::string str_fa; //待匹配串
	std::string str_son; //子串
	void get_next ( )
	{
		memset ( next, 0, sizeof ( next ) );
		int i = 0; int j = -1;
		next[0] = -1;
		int len = str_son.size();
		while ( i < len )
			if ( j == -1 || str_son[i] == str_son[j] )
			{
				i++;
				j++;
				next[i] = j;
			}
			else
				j = next[j];
	}
	int KMP ( int pos ) //匹配起始位置为str_fa[pos]
	{
		int i = pos;
		int j = -1;
		int len_fa =str_fa.size();
		int len_son =str_son.size();
		get_next();
		while ( i < len_fa && j < len_son )
		{
			if ( j == -1 || str_fa[i] == str_son[j] )
			{
				i++;
				j++;
			}
			else
				j = next[j];
		}
		if(j >= len_son)
			return i-len_son; //返回字串第一次出现位于父串位置。
		return 0;

	}
}

namespace hash
{

}

namespace big
{
	//高精度数字类
}

//LCA
