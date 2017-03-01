#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node
{
	int a, b;
	vector<char> steps;
	Node(int _A, int _B) :a(_A), b(_B) {}
};

void output(const vector<char> &_S)
{
	//0,1:fill
	//2,3:drop
	//4,5:pour(x,y) x->y
	cout << _S.size() << endl;
	for (int i = 0; i < _S.size(); ++i)
	{
		int step = _S[i];
		if (step == 0)
		{
			cout << "FILL(1)" << endl;
		}
		else if (step == 1)
		{
			cout << "FILL(2)" << endl;
		}
		else if (step == 2)
		{
			cout << "DROP(1)" << endl;
		}
		else if (step == 3)
		{
			cout << "DROP(2)" << endl;
		}
		else if (step == 4)
		{
			cout << "POUR(1,2)" << endl;
		}
		else
		{
			cout << "POUR(2,1)" << endl;
		}
	}
}

int main()
{
	//6入口BFS
	int A, B, C;
	cin >> A >> B >> C;
	vector<vector<bool> > vst(A + 1, vector<bool>(B + 1, false));
	Node node(0, 0);
	queue<Node> q;
	while (!q.empty()) q.pop();
	q.push(node);
	vst[node.a][node.b] = true;
	bool ok = false;
	while (!q.empty())
	{
		node = q.front();
		q.pop();
		if (node.a == C || node.b == C)
		{
			output(node.steps);
			ok = true;
			break;
		}
		else
		{
			{//fill a
				Node nxt(node);
				nxt.a = A;
				nxt.steps.push_back(0);
				if (!vst[nxt.a][nxt.b])
				{
					vst[nxt.a][nxt.b] = true;
					q.push(nxt);
				}
			}
			{//fill b
				Node nxt(node);
				nxt.b = B;
				nxt.steps.push_back(1);
				if (!vst[nxt.a][nxt.b])
				{
					vst[nxt.a][nxt.b] = true;
					q.push(nxt);
				}
			}
			{//drop a
				Node nxt(node);
				nxt.a = 0;
				nxt.steps.push_back(2);
				if (!vst[nxt.a][nxt.b])
				{
					vst[nxt.a][nxt.b] = true;
					q.push(nxt);
				}
			}
			{//drop b
				Node nxt(node);
				nxt.b = 0;
				nxt.steps.push_back(3);
				if (!vst[nxt.a][nxt.b])
				{
					vst[nxt.a][nxt.b] = true;
					q.push(nxt);
				}
			}
			{//pour 1,2
				Node nxt(node);
				if (nxt.a + nxt.b <= B)
				{
					nxt.b += nxt.a;
					nxt.a = 0;
				}
				else
				{
					nxt.a -= (B - nxt.b);
					nxt.b = B;
				}
				nxt.steps.push_back(4);
				if (!vst[nxt.a][nxt.b])
				{
					vst[nxt.a][nxt.b] = true;
					q.push(nxt);
				}
			}
			{//pour 2,1
				Node nxt(node);
				if (nxt.a + nxt.b <= A)
				{
					nxt.a += nxt.b;
					nxt.b = 0;
				}
				else
				{
					nxt.b -= (A - nxt.a);
					nxt.a = A;
				}
				nxt.steps.push_back(5);
				if (!vst[nxt.a][nxt.b])
				{
					vst[nxt.a][nxt.b] = true;
					q.push(nxt);
				}
			}

		}
	}
	if (!ok)
	{
		cout << "impossible" << endl;
	}
	return 0;
}
