#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define forn(i,n) for(int i=0;i<int(n);++i)
int n;
int g[501][501];
vector<int> w;
bool used[501];
int maxw,p[501],answ,ansp[501];
bool used2[501];

bool kuhn(int v)
{
	if(used[v]) return false;
	used[v]=true;
	forn(j,n)
		if(g[v][j]<=maxw)
			if(p[j]==-1 || kuhn(p[j]))
			{
				p[j]=v;
				return true;
			}
	return false;
}

inline bool check()
{
	forn(i,n)
		if(p[i]==-1) return false;
	return true;
}

void main()
{
	scanf("%d",&n);
	w.reserve(n*n);
	forn(i,n)
		forn(j,n)
		{
			int a;
			scanf("%d",&a);
			g[i][j]=a;
			w.push_back(a);
		}
	sort(w.begin(),w.end());
	int lf=0;
	int rg=unique(w.begin(),w.end())-w.begin();
	forn(i,25)
	{
		int mid=lf+(rg-lf)/2;
		maxw=w[mid];
		memset(p,-1,sizeof(p));
		memset(used2,0,sizeof(used2));
		forn(i,n)
		{
			forn(j,n)
				if(p[j]==-1 && g[i][j]<=maxw)
				{
					p[j]=i;
					used2[i]=true;
					break;
				}
		}
		forn(i,n)
			if(!used2[i])
			{
				memset(used,0,sizeof(used));
				kuhn(i);
			}
		if(check())
		{
			rg=mid;
			answ=maxw;
			memcpy(ansp,p,sizeof(p));
		} else lf=mid;
	}
	printf("%d\n",answ);
	forn(i,n)
		printf("%d %d\n",ansp[i]+1,i+1);
}