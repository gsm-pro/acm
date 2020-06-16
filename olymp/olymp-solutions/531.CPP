#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
vector<vector<__int64>> d;
map<pair<__int64,__int64>,int> pt;
int n;
__int64 x[1501],y[1501];

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>n;
	d.resize(n);
	for (int i=0;i<n;i++)
	{
		cin>>x[i]>>y[i];
		d[i].resize(n);
		pt[make_pair(x[i],y[i])]++;
	}
	for (int i=0;i<n;i++)
		for (int j=i+1;j<n;j++)
			d[j][i]=d[i][j]=(x[j]-x[i])*(x[j]-x[i])+(y[j]-y[i])*(y[j]-y[i]);
	for (int i=0;i<n;i++)
		sort(d[i].begin(),d[i].end());
	__int64 ans=0;
	for (int i=0;i<n;i++)
	{
		__int64 kol=0;
		for (int j=0;j<n+1;j++)
			if (j==0 || j==n || d[i][j]!=d[i][j-1])
				ans+=kol*(kol-1)/2,kol=1;else kol++;
	}
	for (int i=0;i<n;i++)
	{
		for (int j=i+1;j<n;j++)
		{
			__int64 xx=(x[i]+x[j])/2,yy=(y[i]+y[j])/2;
			if (xx+xx!=x[i]+x[j] || yy+yy!=y[i]+y[j]) continue;
			if (pt.count(make_pair(xx,yy))>0) ans--;
		}
	}
	cout<<ans;
}