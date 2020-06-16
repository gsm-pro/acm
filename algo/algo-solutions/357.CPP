#include<iostream>
#include<vector>
#include<map>
#include<set>
using namespace std;
#define forn(i,n) for(int i=0;i<int(n);++i)
#define X first
#define Y second
#define mp(a,b) make_pair(a,b)
typedef pair<short,short> pt;
const int VMAX=6000;
int n,m;
pt p[VMAX];
map<int,set<int>>mr;
int d[VMAX];
bool used[VMAX];
short pr[VMAX];

inline int len(int a,int b)
{
	return (p[a].X-p[b].X)*(p[a].X-p[b].X)+(p[a].Y-p[b].Y)*(p[a].Y-p[b].Y);
}

void main()
{
	scanf("%d",&n);
	forn(i,n)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		p[i]=mp(a,b);
	}
	scanf("%d",&m);
	forn(i,m)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		--a;--b;
		mr[a].insert(b);
		mr[b].insert(a);
	}
	memset(used,0,sizeof(used));
	memset(d,127,sizeof(d));
	memset(pr,-1,sizeof(pr));
	d[0]=0;
	set<pair<int,short>> sr;
	sr.insert(mp(0,0));
	while(true)
	{
		int v=-1;
		while(sr.size()>0)
		{
			int tmp=sr.begin()->second;
			int tmpw=sr.begin()->first;
			sr.erase(sr.begin());
			if(!used[tmp])
			{
				v=tmp;
				if(tmpw!=0 && pr[v]!=-1) printf("%d %d\n",pr[v]+1,v+1);
				break;
			}
		}
		if(v==-1) break;
		used[v]=true;		
		forn(i,n)
		{
			if(!used[i])
			{
				int w;
				if(mr[v].count(i))
					w=0;
				else
					w=len(v,i);
				if(w<d[i])
				{
					sr.erase(mp(d[i],i));
					d[i]=w;
					pr[i]=v;
					sr.insert(mp(w,i));
				}
			}
		}
	}
}