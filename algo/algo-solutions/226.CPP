#include<iostream>
#include<vector>
#include<map>
using namespace std;
const int inf=1<<30;
map<pair<int,int>,int> pt;
vector<pair<int,int>> e;

int main()
{
	int n=0,m;
	cin>>m;
	for (int i=0;i<m;i++)
	{
		int x,y,z,w;
		cin>>x>>y>>z>>w;
		if (pt.count(make_pair(x,y))==0)
		{
			pt[make_pair(x,y)]=n;
			n++;
		}
		if (pt.count(make_pair(z,w))==0)
		{
			pt[make_pair(z,w)]=n;
			n++;
		}
		int a=pt[make_pair(x,y)],b=pt[make_pair(z,w)];
		e.push_back(make_pair(a,b));
	}
	int x,y,z,w;
	cin>>x>>y>>z>>w;
	int ss=pt[make_pair(x,y)],tt=pt[make_pair(z,w)];
	for (int i=0;i<(int)e.size();i++)
	{
		if (e[i].first==ss) e[i].first=0;else
			if (e[i].first==0) e[i].first=ss;else
				if (e[i].first==tt) e[i].first=n-1;else
					if (e[i].first==n-1) e[i].first=tt;
		if (e[i].second==ss) e[i].second=0;else
			if (e[i].second==0) e[i].second=ss;else
				if (e[i].second==tt) e[i].second=n-1;else
					if (e[i].second==n-1) e[i].second=tt;
	}
	vector<vector<int>> c(2*n,vector<int>(2*n));
	vector<vector<int>> f(2*n,vector<int>(2*n));
	for(int i=0;i<m;++i)
	{
		int a=n,b=n;
		if(e[i].first==0 || e[i].first==n-1) a=0;
		if(e[i].second==0 || e[i].second==n-1) b=0;
		c[e[i].first][e[i].first+a]=1;
		c[e[i].first+a][e[i].second]=1;
		c[e[i].second][e[i].second+b]=1;
		c[e[i].second+b][e[i].first]=1;
	}
	while (true)
	{
		vector<int> from(2*n,-1);
		vector<int> q(2*n);
		int h=0,t=0;
		q[t++]=0,from[0]=0;
		for (int cur;h<t;)
		{
			cur=q[h++];
			for (int v=0;v<2*n;v++)
				if (from[v]==-1 && c[cur][v]-f[cur][v]>0)
				{
					if (v>=n && cur!=v-n) continue; 
					q[t++]=v;
					from[v]=cur;
				}
		}
		if (from[n-1]==-1)
			break;
		int cf=inf;
		for (int cur=n-1;cur!=0;)
		{
			int prev=from[cur];
			cf=min(cf,c[prev][cur]-f[prev][cur]);
			cur=prev;
		}
		for (int cur=n-1;cur!=0;)
		{
			int prev=from[cur];
			f[prev][cur]+=cf;
			f[cur][prev]-=cf;
			cur=prev;
		}
	}
	int fl=0;
	for (int i=0;i<2*n;++i)
		if (c[0][i])
			fl+=f[0][i];
	cout<<max(fl,0);
}