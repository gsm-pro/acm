#include<vector>
#include<iostream>
#include<queue>
using namespace std;
int n,m;
vector<vector<int>> f,c;
vector<bool> us;
vector<int> p;

int cf(int u,int v)
{
	return c[u][v]-f[u][v];
}

void bfs()
{
	queue<int> q;
	us.assign(2*n,false);
	p.assign(2*n,-1);
	q.push(0);
	us[0]=true;
	while (!q.empty())
	{
		int v=q.front();
		q.pop();
		for (int u=0;u<2*n;u++)
		{
			if (us[u]) continue;
			if (cf(v,u)==0) continue;
			us[u]=true;
			p[u]=v;
			q.push(u);
		}
	}
}

int flow()
{
	int ans=0;
	while (true)
	{
		bfs();
		if (p[2*n-1]==-1) break;
		for (int v=2*n-1;p[v]!=-1;v=p[v])
		{
			int u=p[v];
			f[u][v]++,f[v][u]--;
		}
		ans++;
	}
	return ans;
}

int main()
{
	cin>>n>>m;
	f.resize(2*n,vector<int>(2*n,0));
	c.resize(2*n,vector<int>(2*n,0));
	us.resize(2*n,false);
	p.resize(2*n,-1);
	for (int i=0;i<n;i++)
		c[i][i+n]++,c[i+n][i]++;
	for (int i=0;i<m;i++)
	{
		int s,t;
		cin>>s>>t;
		--s,--t;
		c[s][t+n]++,c[t][s+n]++;
	}
	int k=flow();
	cout<<k<<endl;
	for (int i=0;i<k;i++)
	{
		vector<int> way;
		int v=2*n-1;
		way.push_back(n-1);
		do 
		{
			for (int u=0;u<2*n-1;u++)
				if (f[u][v]==1)
				{
					if (abs(v-u)==n) way.push_back(min(u,v));
					f[u][v]--;
					f[v][u]++;
					v=u;
					break;
				}
		} while (v!=0);
		way.push_back(0);
		for (int j=(int)way.size()-1;j>-1;--j) cout<<way[j]+1<<" ";
		cout<<endl;
	}
}