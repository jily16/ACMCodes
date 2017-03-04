/**************************************
**	author:jily
**	update:3/4/2017
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
		if (rank[x] > rank[y]) s[y] = x;
		else if (rank[x] == rank[y])	//等高集更新秩
		{
			s[x] = y;
			++rank[y];
		}
		else s[x] = y;
	}
}

namespace graph
{
	//拓扑排序
	//Directed Acyclic Graph(DAG)
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
}
