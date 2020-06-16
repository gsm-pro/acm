#include<iostream>
#include<vector>
using namespace std;
typedef long long LL;
typedef vector<LL> vint;
const LL NO=1ll*1000000000000000000;
vint t;
int n;

void build(const vint &a,int i,int l,int r)
{
	if (l==r) t[i]=a[l];else
	{
		int m=(l+r)>>1;
		build(a,i+i,l,m);
		build(a,i+i+1,m+1,r);
	}
}

void update(int i,int l,int r,int x,int y,LL val)
{
	if (l==x && r==y) t[i]=val;else
	{
		if (t[i]!=NO)
		{
			t[i+i]=t[i+i+1]=t[i];
			t[i]=NO;
		}
		int m=(l+r)>>1;
		if (x<=m) update(i+i,l,m,x,min(y,m),val);
		if (y>m) update(i+i+1,m+1,r,max(x,m+1),y,val);
	}
}

LL sum(int i,int l,int r,int x,int y)
{
	if (t[i]!=NO) return t[i]*(y-x+1);
	int m=(l+r)>>1;
	LL result=0;
	if (x<=m) result+=sum(i+i,l,m,x,min(y,m));
	if (y>m) result+=sum(i+i+1,m+1,r,max(x,m+1),y);
	return result;
}

LL get(int x)
{
	int i=1,l=0,r=n-1;
	while (t[i]==NO)
	{
		if (l==r) return 0;
		int m=(l+r)>>1;
		if (x<=m) i=i+i,r=m;else i=i+i+1,l=m+1;
	}
	return t[i];
}

int main()
{
	int m;
	scanf_s("%d%d",&n,&m);
	vint a(n);
	for (int i=0,j;i<n;++i) scanf_s("%d",&j),a[i]=j;
	t.assign(n*4, NO);
	build(a,1,0,n-1);
	LL s0=sum(1,0,n-1,0,n-1),s1=s0;
	for (int i=0;i<m;++i)
	{
		int x,y;
		scanf_s("%d%d",&x,&y);
		--x,--y;
		LL s=sum(1,0,n-1,x,y),m=s/(y-x+1),mod=s%(y-x+1);
		if (mod<0) --m;
		if (mod&&s1<=s0) ++m;
		s1-=s;
		s1+=m*1ll*(y-x+1);
		update(1,0,n-1,x,y,m);
	}
	for (int i=0;i<n;++i) printf("%lld ",get(i));
}