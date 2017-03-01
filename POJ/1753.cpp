#include <iostream>
using namespace std;

const long long MAX_CHOICE = (1 << 16) - 1;
const long long ALL_BLACK = (1 << 16) - 1;
int flip[] = { 0xC800,0xE400,0x7200,0x3100,0x8C80,0x4E40,0x2720,0x1310,0x08C8,0x04E4,0x0272,0x0131,0x008C,0x004E,0x0027,0x0013 };
int search(long long _ori)
{
	if (_ori == 0 || _ori == ALL_BLACK)
	{
		return 0;
	}
	else
	{
		int ans = 17;
		for (long long choice = 0; choice <= MAX_CHOICE; ++choice)	//每一个策略
		{
			int ori = _ori;
			int highest_bit = 1;	//标记最高位
			int step = 0;
			for (int index = 0; index < 16; ++index)	//每一位
			{
				if (highest_bit == (highest_bit & choice))	//反转这一位
				{
					++step;
					ori ^= flip[15 - index];	//完成反转
					if (ori == 0 || ori == ALL_BLACK)
					{
						if (step < ans)
						{
							ans = step;
						}
						break;
					}
				}
				highest_bit <<= 1;
			}
		}
		return ans;
	}
}

int main()
{
	long long ori = (1 << 16) - 1;
	char c;
	for (int i = 0; i < 16; ++i)
	{
		cin >> c;
		if (c == 'w')
		{
			ori ^= (1 << (15 - i));
		}
	}
	int ans = search(ori);
	if (ans < 17)
	{
		cout << ans << endl;
	}
	else
	{
		cout << "Impossible\n";
	}
	return 0;
}
