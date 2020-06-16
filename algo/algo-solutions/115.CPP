#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<queue>
using namespace std;
#define forn(i,n) for(int(i)=0;i<n;i++)
#define nmax 201
#define inf INT_MAX>>1
int c[nmax][nmax],e[nmax],h[nmax];
int n,s,t;
queue<int> q;

void Push(int u,int v)
{
	int add=min(e[u],c[u][v]);
	if((!e[v]) && (v!=s) && (v!=t)) q.push(v);
	e[u]-=add,e[v]+=add;
	c[u][v]-=add,c[v][u]+=add;
}

void Lift(int u)
{
	int minh=inf;
	forn(i,n)
		if (c[u][i]) minh=min(minh,h[i]);
	h[u]=minh+1;
}

void Discharge(int u)
{
	int cur=0;
	while (e[u]>0)
	{
		if (cur==n) 
		{ 
			Lift(u); 
			cur=0; 
			continue; 
		}
		if (c[u][cur] && h[u]==h[cur]+1) Push(u,cur);
		cur++;
	}
}

void Init()
{
	forn(i,n)
	{
		if (i!=s)
		{
			e[i]=c[s][i];
			c[i][s]+=c[s][i];
			h[i]=0;
		} else h[i]=n;
	}
}

int main()
{
	scanf("%d",&n);
	forn(i,n)
		forn(j,n) 
			scanf("%d",&c[i][j]);
	s=0,t=n-1;
	forn(i,n) c[i][i]=0;
	Init();
	forn(i,n) 
		if(e[i] && i!=t) q.push(i);
	while (!q.empty())
	{
		int j=q.front();
		q.pop();
		Discharge(j);
	}
	printf("%d",e[t]);
}