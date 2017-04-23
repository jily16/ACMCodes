#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
int main()
{
#ifdef DEBUG
	freopen("C:\\Users\\admin\\Desktop\\编程\\in.txt", "r", stdin);
#endif

	int n;
	cin >> n;
	priority_queue<int> pq; while (!pq.empty()) pq.pop();
	int l;
	long long sum = 0;
	while (n--)
	{
		cin >> l;
//		sum += l;
		pq.push(-l);
	}
	long long cost = 0;
	while (pq.size() > 1)
	{
		int tp1 = pq.top();
		pq.pop();
//		cout << "Out " << tp1 << ", ";
		int tp2 = pq.top();
		pq.pop();
//		cout << "out " << tp2 << endl;
		int ne = tp1 + tp2;
		pq.push(ne);
//		cost += sum;
//		cout << "cost += " << sum << endl;
//		sum -= tp;
		cost -= ne;
	}
	cout << cost << endl;

#ifdef DEBUG
	freopen("con", "r", stdin);
	system("pause");
#endif // DEBUG
	return 0;
