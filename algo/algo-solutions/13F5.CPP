#include<iostream>
#include<vector>
#include<queue>
using namespace std;
#define forn(i,n) for(int i=0;i<int(n);++i)
const int NMAX=201;
int n,m,c[NMAX][NMAX],f[NMAX][NMAX];

bool enlarge(int s,int t)
{
	bool u[NMAX];
	int p[NMAX],mf[NMAX];
	memset(u,0,sizeof(u));
	memset(p,-1,sizeof(p));
	memset(mf,127,sizeof(mf));
	queue<int> q;
	u[s]=true;
	p[s]=s;
	q.push(s);
	while (!q.empty() && !u[t])
	{
		int v=q.front();
		q.pop();
		forn(j,n)
		{
			if(!u[j] && c[v][j]-f[v][j]>0)
			{
				u[j]=true;
				p[j]=v;
				mf[j]=min(mf[v],c[v][j]-f[v][j]);
				q.push(j);
			}
		}
	}
	if(!u[t])
		return false;
	for(int v=t;v!=p[v];v=p[v])
	{
		f[p[v]][v]+=mf[t];
		f[v][p[v]]-=mf[t];
	}
	return true;
}

void pdec(int v)
{
	if (v==0)
		return;
	forn(j,n)
	{
		if (f[v][j]<0)
		{
			f[v][j]++;
			f[j][v]--;
			pdec(j);
			break;
		}
	}
}

void fdec(int v)
{
	if (v==n-1)
		return;
	forn(j,n)
	{
		if (f[v][j]>0)
		{
			f[v][j]--;
			f[j][v]++;
			fdec(j);
			break;
		}
	}
}

int main()
{
	memset(c,0,sizeof(c));
	memset(f,0,sizeof(f));
	cin>>n>>m;
	forn(i,m)
	{
		int a,b,d;
		cin>>a>>b>>d;
		--a;--b;
		c[a][b]=d;
	}
	while(enlarge(0,n-1));
	int ans = 0;
	forn(j,n)
		ans+=f[0][j];
	cout<<ans<<endl;
	int op;
	cin>>op;
	forn(k,op)
	{
		int type,a,b;
		cin>>type>>a>>b;
		--a;--b;
		if (type==1)
		{
			c[a][b]++;
			if ((f[a][b]==c[a][b]-1) && enlarge(0,n-1)) ans++;
		}
		else
		{
			c[a][b]--;
			if (f[a][b]>c[a][b])
			{
				ans--;
				f[a][b]=c[a][b];
				f[b][a]=-f[a][b];
				pdec(a);
				fdec(b);
				if (enlarge(0,n-1)) ans++;
			}
		}
		cout<<ans<<endl;
	}
}