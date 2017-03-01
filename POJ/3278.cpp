#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Node
{
	int x;
	int step;
};
vector<Node> get_nxts(Node _N)
{
	vector<Node> ret;
	ret.push_back(Node{ _N.x - 1,_N.step + 1 });
	ret.push_back(Node{ _N.x + 1,_N.step + 1 });
	ret.push_back(Node{ _N.x * 2,_N.step + 1 });
	return ret;
}
int main()
{
	int n, k;
	cin >> n >> k;
	vector<bool> vst(100005, false);
	queue<Node> q;
	while (!q.empty()) q.pop();
	Node node{ n,0 };
	q.push(node);
	vst[node.x] = true;
	int steppp = -1;
	while (!q.empty())
	{
		node = q.front();
		q.pop();
		if (node.x == k)
		{
			steppp = node.step;
			break;
		}
		else
		{
			vector<Node> nxts = get_nxts(node);
			Node nxt;
			for (int i = 0; i < 3; ++i)
			{
				nxt = nxts[i];
				if (nxt.x >= 0 && nxt.x <= 100000 && !vst[nxt.x])
				{
					vst[nxt.x] = true;
					q.push(nxt);
				}
			}
		}
	}
	cout << steppp << endl;
	return 0;
}
