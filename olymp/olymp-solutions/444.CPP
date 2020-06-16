#include<fstream>

int main()
{
	__int64 ans[61],n;
	std::ifstream("input.txt")>>n;
	ans[1]=2;
	for (int i=2;i<=60;i++)
	{
		ans[i]=1LL<<i;
		for (int j=1;j<=i/2;j++)
			if (i%j==0) ans[i]-=ans[j];
	}
	std::ofstream("output.txt")<<ans[n];
}