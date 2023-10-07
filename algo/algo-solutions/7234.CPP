#include<iostream>
#include<vector>
#include<algorithm>
#define forn(i,n) for(int i=0;i<(int)(n);++i)
using namespace std;
const int INF=1000000000;
const int N=2500;
vector<int> g[N];
bool us[N];
int maxDist;

void dfs(int nx,int dist)
{
	if(us[nx]) return;
	us[nx]=true;
	maxDist=max(maxDist,dist);
	forn(i,g[nx].size()) dfs(g[nx][i],dist+1);
}

void main()
{
	int n;
	cin>>n;
	forn(w,n-1)
	{
		int t,u;
		cin>>t>>u;
		--t,--u;
		g[t].push_back(u);
		g[u].push_back(t);
	}
	vector<int> ans;
	int low=INF;
	forn(i,n)
	{
		maxDist=0;
		memset(us,false,sizeof(us));
		dfs(i,0);        
		if (low>maxDist)
		{
			ans.clear();
			low=maxDist;
			ans.push_back(i);
		} else 
			if(low==maxDist) ans.push_back(i);
	}
	cout<<ans.size()<<endl;
	forn(i,ans.size()) cout<<ans[i]+1<<endl;
}