#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int n,m,timer,tin[555],f[555];;
bool dls[555],cb[555],ts[555],u[555];
vector<int> g[555];

void go(int v)
{
	++timer;
	tin[v]=timer;
	f[v]=timer;
	u[v]=true;
	for (int i=0;i<(int)g[v].size();i++)
	{
		int nv=g[v][i];
		if (dls[nv]) continue;
		if (u[nv]) f[v]=min(f[v],tin[nv]);else
		{
			go(nv);
			f[v]=min(f[v],f[nv]);
			if (tin[v]<=f[nv]) ts[v]=true;
		}
	}
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>n>>m;
	for (int i=0;i<m;i++)
	{
		int x,y;
		cin>>x>>y;
		g[x-1].push_back(y-1);
		g[y-1].push_back(x-1);
	}
	memset(dls,0,sizeof dls);
	memset(cb,0,sizeof cb);
	for (int i=0;i<(int)g[0].size();i++) cb[g[0][i]]=true;
	vector<int> res;
	for (int i=0;i<n-1;i++)
	{
		memset(u,0,sizeof u);
		memset(ts,0,sizeof ts);
		timer=0;
		go(0);
		int v=-1;
		for (int t=0;t<n;t++)
		{
			if (t>0 && !dls[t] && cb[t] && !ts[t])
			{
				v=t;
				break;
			}
		}
		res.push_back(v+1);
		dls[v]=true;
		for (int t=0;t<(int)g[v].size();t++) cb[g[v][t]]=true;
	}
	cout<<1;
	for (int i=0;i<(int)res.size();i++) cout<<" "<<res[i];
	cout<<endl;
	reverse(res.begin(),res.end());
	cout<<1;
	for (int i=0;i<(int)res.size();i++) cout<<" "<<res[i];
	cout<<endl;
}