#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

bool isp(int n)
{
	for (int i = 2; i < sqrt(n) + 1; ++i)
	{
		if (n%i == 0)
			return false;
	}
	return true;
}

struct Node
{
	int num;
	int step;
	Node(int _Num, int _Step) :num(_Num), step(_Step) {}
};

void bfs(int m, int n)
{
	vector<bool> vst(10000, false);
	queue<Node> q;
	while (!q.empty()) q.pop();
	Node node(m, 0);
	q.push(node);
	vst[node.num] = true;
	while (!q.empty())
	{
		node = q.front();
		q.pop();
		if (node.num == n)
		{
			cout << node.step << endl;
			return;
		}
		else
		{
			int ori_num = node.num;
			Node nxt(ori_num, node.step + 1);
			nxt.num = ori_num;
			for (int i = 0; i <= 9; ++i)
			{
				nxt.num -= (nxt.num % 10);
				nxt.num += i;
				if (isp(nxt.num) && !vst[nxt.num])
				{
					vst[nxt.num] = true;
					q.push(nxt);
				}
			}
			nxt.num = ori_num;
			for (int i = 0; i <= 9; ++i)
			{
				nxt.num -= (10 * ((nxt.num / 10) % 10));
				nxt.num += (10 * i);
				if (isp(nxt.num) && !vst[nxt.num])
				{
					vst[nxt.num] = true;
					q.push(nxt);
				}
			}
			nxt.num = ori_num;
			for (int i = 0; i <= 9; ++i)
			{
				nxt.num -= (100 * ((nxt.num / 100) % 10));
				nxt.num += 100 * i;
				if (isp(nxt.num) && !vst[nxt.num])
				{
					vst[nxt.num] = true;
					q.push(nxt);
				}
			}
			nxt.num = ori_num;
			for (int i = 1; i <= 9; ++i)
			{
				nxt.num -= (1000 * (nxt.num / 1000));
				nxt.num += 1000 * i;
				if (isp(nxt.num) && !vst[nxt.num])
				{
					vst[nxt.num] = true;
					q.push(nxt);
				}
			}

		}
	}
	cout << "Impossible" << endl;
}

int main()
{
	int t;
	cin >> t;
	int m, n;
	while (t--)
	{
		cin >> m >> n;
		bfs(m, n);
	}
	return 0;
}
