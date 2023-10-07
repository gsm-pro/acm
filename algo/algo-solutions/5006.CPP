#include<iostream>
#include<algorithm>
using namespace std;
#define forn(i,n) for (int i=0;i<n;i++)
#define NMAX 100001
int zn[NMAX],op[NMAX],n,m;
int elem[NMAX],tree[NMAX];
bool values[NMAX];

int find(int zn)
{
	int m,l=0,r=n-1;
	while (r-l>1)
	{
		m=(l+r)>>1;
		if (elem[m]>zn) r=m;else l=m;
	}
	if (elem[l]==zn) return l;else return r;
}

void update(int x,int c)
{
	while (x<=n) tree[x]+=c,x=x|(x+1);
}

int get(int x)
{
	int res=0;
	while (x>0) res+=tree[x],x=(x&(x+1))-1;
	return res;
}

int main()
{
	scanf("%d\n",&m);
	char tmp[10];
	forn(i,m)
	{
		scanf("%s%d",&tmp,&zn[i]);
		elem[i]=zn[i];
		if (tmp[1]=='D') op[i]=1;
		if (tmp[1]=='E') op[i]=-1;
		if (tmp[1]=='N') op[i]=0;
	}
	sort(elem,elem+m);
	n=0;
	forn(i,m)
		if ((i==0)||(elem[i]!=elem[i-1])) elem[n++]=elem[i];
	memset(tree,0,sizeof(tree));
	memset(values,0,sizeof(values));
	int x;
	forn(i,m)
	{
		x=find(zn[i])+1;
		if (op[i]==1 && (!values[x]))
		{
			update(x,1);
			values[x]=true;
		}
		if (op[i]==-1 && (values[x]))
		{
			update(x,-1);
			values[x]=false;
		}
		if (op[i]==0)
			if (values[x]) printf("%d\n",get(x)-1);else printf("-1\n");
	}
}