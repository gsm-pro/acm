#include<iostream>
using namespace std;
int x[5555],y[5555],s[15555],n,ans=1<<22;

int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	cin>>n;
	for (int i=0;i<n;i++) 
	{
		cin>>x[i]>>y[i];
		s[x[i]]++;
		if (x[i]!=y[i]) s[y[i]]++;
	}
	for (int i=0;i<=9998;i++)
		for (int j=i+1;j<=9999;j++)
			ans=min(ans,2*n-s[i]-s[j]);
	for (int i=0;i<=9999;i++)
	{
		int t=0;
		for (int j=0;j<n;j++)
			if (x[j]==i && y[j]==i);else
				if (x[j]!=i && y[j]!=i) t+=2;else t++;
		ans=min(ans,t);
	}
	cout<<ans;
}