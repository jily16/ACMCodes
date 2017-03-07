/**************************************
**	author:jily
**	update:3/7/2017
**	说明
**	为了妥协POJ等一系列OJ平台的落伍
**		模板不采用C++11以后的新特性
**			中文逗号太丑所以本文宁愿用换行加缩进
**	图结构的表示默认采用邻接矩阵
**************************************/

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int const INF = 0x3f3f3f3f;	//神奇的无穷大

namespace ufs
{
	//并查集Union-Find算法
	//按秩合并
		//因为维护成本
			//不路径压缩
	void init_set(vector<int> &s, vector<int> &rank)
	{
		for (int i = 0; i < s.size(); ++i) s[i] = i;
		for (int i = 0; i < rank.size(); ++i) rank[i] = 1;	//秩属性加速后期的查找
	}
	int find_key(vector<int> const &s, int x)
	{
		while (x != s[x]) x = s[x];	//迭代求法
		return x;
	}
	void union_set(vector<int> &s, vector<int> &rank, int x, int y)
	{
		if (find_key(s, x) == find_key(s, y)) return;
		if (rank[x] > rank[y]) s[find_key(s, y)] = x;	//始终应更新根节点或者叫代表节点
		else if (rank[x] == rank[y])
		{
			s[find_key(s, x)] = y;
			++rank[y];
		}
		else s[find_key(s, x)] = y;
	}
}

namespace graph
{
	//拓扑排序
	//Directed Acyclic Graph(DAG)
	//返回true说明没有死锁
	bool torpological_sort(vector<vector<int> > const &g)
	{
		int n = g.size();
		vector<int> d(n);	//入度数组
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
			cout << d0 << endl;
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

	//Prim算法获得最小生成树(全径权值)
	//模板题POJ1251
	//感谢博主http://www.cnblogs.com/Veegin/archive/2011/04/29/2032388.html提供优秀的做法
	int prim(vector<vector<int> > const &g)
	{
		int n = g.size();	//顶点数
		int sum = 0;
		vector<bool> vst(n, false);	//visited就是已经在树上
		vector<int> closest(n);
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
									//可以考虑一下priority_queue怎么写可以提速
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
		int n = g.size();
		vector<int> ufs(n);	//并查集
		vector<int> rank(n);
		for (int i = 0; i < n; ++i)	//初始化并查集
		{
			ufs[i] = i;
			rank[i] = 1;
		}
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
			if (ufs::find_key(ufs, e.v1) != ufs::find_key(ufs, e.v2))	//在某一分量之内则忽略
			{
				sum += e.weight;
				//其他操作
				ufs::union_set(ufs, rank, e.v1, e.v2);	//加入分量
			}
		}
		return sum;
	}

	//最短路径问题
	//松弛边<u,v>
		//Dijkstra和Bellman-Ford的共同必要操作
	//d是点到源节点地距离
	void relax(vector<vector<int> > const &g, vector<int> &d, int u, int v)
	{
		if (d[v] > d[u] + g[u][v])
		{
			d[v] = d[u] + g[u][v];
				//如果有前驱子图要维护的话就应该在这
		}
	}

	//Dijkstra算法
		//边权非负的有向图的最短路径
	int dijkstra(vector<vector<int> > const &g, int s, int v)
	{
		int n = g.size();
		vector<int> d(n);	//到源节点距离
		for (int i = 0; i < n; ++i)	//这是一步初始化
		{
			d[i] = g[s][i];
		}
		vector<bool> vst(n, false);
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
						relax(g, d, min_d_pos, i);
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
		//d数组不用外部置数
			//直接给一个新数组就行~
	bool bellman_ford(vector<vector<int>> const &g, vector<int> &d, int s)
	{
		int n = g.size();
		for (int i = 0; i < n; ++i)	//初始化d数组
		{
			d[i] = g[s][i];
		}
		for (int i = 0; i < n - 1; ++i)	//核心对所有边进行n-1次松弛
		{
			for (int j = 0; j<n; ++j)
				for (int k = 0; k < n; ++k)
				{
					if (g[j][k] < INF)	//有边
					{
						relax(g, d, j, k);
					}
				}
		}	//至此已经完成d数组的全部松弛工作
			//下面判负权环
		for (int i = 0; i<n; ++i)
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
