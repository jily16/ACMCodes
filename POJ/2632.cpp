#include <map>
#include <iostream>
#include <vector>
using namespace std;
typedef pair<int, char> square;	//机器人编号和朝向

int main()
{
	map<char, char> turnleft;
	turnleft['N'] = 'W';
	turnleft['W'] = 'S';
	turnleft['S'] = 'E';
	turnleft['E'] = 'N';
	map<char, char> turnright;
	turnright['N'] = 'E';
	turnright['E'] = 'S';
	turnright['S'] = 'W';
	turnright['W'] = 'N';
	int k;
	cin >> k;
	int a, b;
	int n, mm;	//n是机器人数量m是指令数
	int tmpx, tmpy;
	char tmpdire;
	while (k--)
	{
		cin >> a >> b;
		vector<vector<square> > v(b, vector<square>(a, square(0, '\0')));
		cin >> n >> mm;
		map<int,/*NO.*/pair<int, int> > m;
		for (int i = 0; i < n; ++i)
		{
			cin >> tmpx >> tmpy >> tmpdire;
			m[i + 1] = make_pair(tmpx - 1, b - tmpy);
			v[b - tmpy][tmpx - 1] = make_pair(i + 1 , tmpdire);
		}
		int noo, repeat;
		char di;
		bool done = false;
		for (int i = 0; i < mm; ++i)
		{
			cin >> noo >> di >> repeat;
			if (di == 'F')
			{
				//cout << "FFFFFFF" << repeat << endl;
				for (int j = 0; j < repeat && !done; ++j)
				{
					//cout << noo << endl;
					//cout << m[noo].second << "^^" << m[noo].first << endl;
					//前进
					switch (v[m[noo].second][m[noo].first].second)
					{
					case 'N':
					{
						if (m[noo].second == 0)
						{
							cout << "Robot " << noo << " crashes into the wall\n";
							done = true;
						}
						else if (v[m[noo].second - 1][m[noo].first].second != '\0')	//撞
						{
							cout << "Robot " << noo << " crashes into robot "
								<< v[m[noo].second - 1][m[noo].first].first << endl;
							done = true;
						}
						else
						{
							v[m[noo].second - 1][m[noo].first].second = v[m[noo].second][m[noo].first].second;
							v[m[noo].second][m[noo].first].second = '\0';
							v[m[noo].second - 1][m[noo].first].first = noo;
							--m[noo].second;
						}
						break;
					}
					case 'W':
					{
						if (m[noo].first == 0)
						{

							cout << "Robot " << noo << " crashes into the wall\n";
							done = true;
						}
						else if (v[m[noo].second][m[noo].first - 1].second != '\0')	//撞
						{
							cout << "Robot " << noo << " crashes into robot "
								<< v[m[noo].second][m[noo].first - 1].first << endl;
							done = true;
						}
						else
						{
							v[m[noo].second][m[noo].first - 1].second = v[m[noo].second][m[noo].first].second;
							v[m[noo].second][m[noo].first].second = '\0';
							v[m[noo].second][m[noo].first-1].first = noo;
							--m[noo].first;
						}
						break;
					}
					case 'S':
					{
						if (m[noo].second == b - 1)
						{

							cout << "Robot " << noo << " crashes into the wall\n";
							done = true;
						}
						else if (v[m[noo].second + 1][m[noo].first].second != '\0')	//撞
						{
							cout << "Robot " << noo << " crashes into robot "
								<< v[m[noo].second + 1][m[noo].first].first << endl;
							done = true;
						}
						else
						{
							v[m[noo].second + 1][m[noo].first].second = v[m[noo].second][m[noo].first].second;
							v[m[noo].second][m[noo].first].second = '\0';
							v[m[noo].second + 1][m[noo].first].first = noo;
							++m[noo].second;
						}
						break;
					}
					case 'E':
					{
						if (m[noo].first == a-1)
						{

							cout << "Robot " << noo << " crashes into the wall\n";
							done = true;
						}
						else if (v[m[noo].second][m[noo].first + 1].second != '\0')	//撞
						{
							cout << "Robot " << noo << " crashes into robot "
								<< v[m[noo].second][m[noo].first + 1].first << endl;
							done = true;
						}
						else
						{
							v[m[noo].second][m[noo].first + 1].second = v[m[noo].second][m[noo].first].second;
							v[m[noo].second][m[noo].first].second = '\0';
							v[m[noo].second][m[noo].first + 1].first = noo;
							++m[noo].first;
							//cout << "current (" << m[noo].first << "," << m[noo].second << endl;
						}
						break;
					}
					default:
						break;
					}
				}
			}
			else
			{
				for (int j = 0; j < repeat; ++j)
				{
					//转向
					if (di == 'L')
						v[m[noo].second][m[noo].first].second = turnleft[v[m[noo].second][m[noo].first].second];
					else
						v[m[noo].second][m[noo].first].second = turnright[v[m[noo].second][m[noo].first].second];
				}
			}
		}
		if (!done)
			cout << "OK\n";
	}
	return 0;
}
