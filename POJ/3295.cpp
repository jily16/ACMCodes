#include <iostream>
#include <set>
#include <stack>
#include <algorithm>
using namespace std;
set<char> pqrst;
int per_test(const string &wff, int p, int q, int r, int s, int t)
{
	stack<int> stk;
	for (int i = wff.size() - 1; i >= 0; --i)
	{
		if (find(pqrst.begin(), pqrst.end(), wff[i]) != pqrst.end())
		{
			switch (wff[i])
			{
			case 'p':
			{
				stk.push(p);
				break;
			}
			case 'q':
			{
				stk.push(q);
				break;
			}
			case 'r':
			{
				stk.push(r);
				break;
			}
			case 's':
			{
				stk.push(s);
				break;
			}
			case 't':
			{
				stk.push(t);
				break;
			}
			}
		}
		else
		{
			switch (wff[i])
			{
			case 'K':
			{
				int last = stk.top();
				stk.pop();
				int K = last & stk.top();
				stk.top() = K;
				break;
			}
			case 'A':
			{
				int last = stk.top();
				stk.pop();
				int A = last | stk.top();
				stk.top() = A;
				break;
			}
			case 'N':
			{
				stk.top() = !stk.top();
				break;
			}
			case 'C':
			{
				int hind = stk.top();
				stk.pop();
				int front = stk.top();
				int C;
				if (front == 0) C = 1;
				else if (hind == 1) C = 1;
				else C = 0;
				stk.top() = C;
				break;
			}
			case 'E':
			{
				int hind = stk.top();
				stk.pop();
				int front = stk.top();
				int E;
				if (hind == front) E = 1;
				else E = 0;
				stk.top() = E;
			}
			default:
				break;
			}
		}
	}
	return stk.top();
}
bool test(const string &wff)
{
	for (int p = 0; p <= 1; ++p)
		for (int q = 0; q <= 1; ++q)
			for (int r = 0; r <= 1; ++r)
				for (int s = 0; s <= 1; ++s)
					for (int t = 0; t <= 1; ++t)
					{
						if (per_test(wff, p, q, r, s, t) == 0)
						{
							return false;
						}
					}
	return true;
}
int main()
{
	pqrst.insert('p');
	pqrst.insert('q');
	pqrst.insert('r');
	pqrst.insert('s');
	pqrst.insert('t');
	string wff;
	while (cin >> wff && wff != "0")
	{
		if (test(wff))
		{
			cout << "tautology\n";
		}
		else
		{
			cout << "not\n";
		}
	}
	return 0;
}
