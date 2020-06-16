#include<iostream>
#include<cmath>
using namespace std;

int main()
{
	double wo, ho, wk, hk;
	while (cin >> wo >> ho >> wk >> hk)
	{
		if (wk < hk) swap(wk, hk);
		if (wo < ho) swap(wo, ho);
		if (ho > hk) cout << "NO"; else
		{
			if (wo <= wk) cout << "YES"; else
			{
				double fc = sqrt(wo * wo + ho * ho - hk * hk),
				bae = acos((double)(-1.0)) / 2 - atan(ho / wo) - atan(fc / hk),
				ge = ho * sin(bae) + wo * cos(bae);
				(ge <= wk + (1e-7)) ? cout << "YES" : cout << "NO";
			}
		}
		cout << endl;
	}
}