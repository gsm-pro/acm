#include<iostream>
#include<vector>
using namespace std;
#define LL long long

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	LL F[20]={1};
	LL c[19][201]={};
	for (int i=1;i<=19;i++) F[i]=F[i-1]*i;
	int n,k,ps=1,h=0;
	cin>>n>>k;
	for (int i=1;i<=18;i++) c[i][0]=1;
	for (int i=2;i<=18;i++)
		for (int j=1;j<=i*(i-1)/2;j++)
			for (int m=0;m<=min(i-1,j);m++)
				c[i][j]+=c[i-1][j-m];
	if (k>n*(n-1)/2)
	{
		cout<<0<<endl<<"-";
		return 0;
	}
	cout<<c[n][k]<<endl;
	LL first[200]={1};
	while (ps<185) 
	{
		h++;
		for (int i=1;i<=h;i++) first[ps]=first[ps-1]+F[h],ps++;
	}
	LL num=first[k]-1;
	vector<int> p(n,0);
	for (int i=0;i<n;i++)
	{
		p[i]=int(num/F[n-i-1])+1;
		num%=F[n-i-1];
	}
	for (int i=n-2;i>=0;i--)
		for (int j=i+1;j<n;j++) if (p[j]>=p[i]) p[j]++;
	copy(p.begin(),p.end(),ostream_iterator<int>(cout," "));
}