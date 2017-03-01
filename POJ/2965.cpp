#include <iostream>
using namespace std;
typedef long long L;
L flip[] =
{
	0xf888,0xf444,0xf222,0xf111,
	0x8f88,0x4f44,0x2f22,0x1f11,
	0x88f8,0x44f4,0x22f2,0x11f1,
	0x888f,0x444f,0x222f,0x111f
};	//1代表要反转
struct Ans
{
	int step;
	L choice;
	Ans(int s, L c) :step(s), choice(c) {}
};
Ans f(L _Ori)
{
	for (L choice = 1; choice <= (1 << 16) - 1; ++choice)
	{
		L ori = _Ori;
		int step = 0;
		L highest = 1;
		for (int i = 0; i < 16; ++i)
		{
			if (((highest << i) & choice) == (highest << i))
			{
				ori ^= flip[15 - i];
				++step;
			}
		}
		if (ori == 0)
		{
			return Ans(step, choice);
		}
		//cout << ori << endl;
		//system("pause");
	}
}
void print_choice(L const &data)
{
	for (int index = 1; index <= 16; ++index)
	{
		if ((data & (1 << (16 - index))) == ((1 << (16 - index))))
		{
			if (index % 4 == 0)
			{
				cout << index / 4 << " 4\n";
			}
			else
			{
				cout << (index / 4) + 1 << " " << (index % 4) << endl;
			}
		}
	}
}
int main()
{
	L ori = (1 << 16) - 1;	//1111111111111111	//1代表关，0代表开
	char c;
	for (int i = 0; i < 16; ++i)
	{
		cin >> c;
		if (c == '-')	//开
		{
			ori ^= (1 << (15 - i));
		}
	}
	Ans ans = f(ori);
	cout << ans.step << endl;
	//cout << ans.choice << endl;
	print_choice(ans.choice);
	//system("pause");
	return 0;
}
