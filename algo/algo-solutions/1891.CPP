#include<iostream>
#include<vector>
#include<queue>
using namespace std;
#define forn(i,n) for(int i=0;i<int(n);++i)
#define mp(a,b) make_pair(a,b)
const int NMAX=10000;
int n,m;
struct edge
{
	int to,f,c,rev;
};
vector<edge> next[NMAX];

void add(int from,int to,int c)
{
	edge forward={to,0,c,(int)next[to].size()};
	edge back={from,0,0,(int)next[from].size()};
	next[to].push_back(back);
	next[from].push_back(forward);
}

bool enlarge(int s,int t)
{
	bool u[NMAX];
	pair<int,int> p[NMAX];
	int mf[NMAX];
	memset(u,0,sizeof(u));
	memset(p,-1,sizeof(p));
	memset(mf,127,sizeof(mf));
	queue<int> q;
	q.push(s);
	u[s]=true;
	p[s]=mp(s,0);
	while(!q.empty() && !u[t])
	{
		int v=q.front();
		q.pop();
		forn(i,next[v].size())
		{
			int to=next[v][i].to;
			if(!u[to])
			{
				int toF=next[v][i].f;
				int toC=next[v][i].c;
				if(toC>toF)
				{
					u[to]=true;
					mf[to]=min(mf[v],toC-toF);
					p[to]=mp(v,i);
					q.push(to);
				}
			}
		}
	}
	if(!u[t]) return false;
	int v=t;
	while(v!=s)
	{
		int to=p[v].second;
		int from=p[v].first;
		next[from][to].f+=mf[t];
		next[v][next[from][to].rev].f-=mf[t];
		v=from;
	}
	return true;
}

int main()
{
	scanf("%d%d",&n,&m);
	forn(i,m)
	{
		int x,y,c;
		scanf("%d%d%d",&x,&y,&c);
		--x;--y;
		add(x,y,c);
	}    
	while(enlarge(0,n-1));
	long long sum=0;
	forn(i,next[0].size()) sum+=next[0][i].f;
	cout<<sum;
}