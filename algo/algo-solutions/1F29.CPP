#include<iostream>
#include<vector>
using namespace std;
#define LL __int64

int main()
{
	LL F[20]={1};
	for (int i=1;i<=19;i++) F[i]=F[i-1]*i;
	vector<int> p;
	int a;
	while (cin>>a) p.push_back(--a);
	LL res=1;
	int n=(int)p.size();
	for (int i=0;i<n;i++) 
	{
		res+=p[i]*F[n-i-1];
		for (int j=i+1;j<n;j++) if (p[j]>=p[i]) p[j]--;
	}
	cout<<n<<" "<<res;
}