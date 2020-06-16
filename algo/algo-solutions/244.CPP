#include <vector>
#include <cstdio>
using namespace std;
#define fn(e1,e2) e1+e2;
vector<int> a,t;
int n;

void build(const vector<int> &a,int i=1,int l=0,int r=n-1)
{
	if (i==1) t.resize(n*4+1);
	if (l==r) t[i]=a[l];else
	{
		int m=(l+r)/2;
		build(a,i*2,l,m);
		build(a,i*2+1,m+1,r);
		t[i]=fn(t[i*2],t[i*2+1]);
	}
}

int res(int l,int r,int i=1,int tl=0,int tr=n-1)
{
	if (l==tl && r==tr) return t[i];
	int m=(tl+tr)/2;
	if (r<=m) return res(l,r,i*2,tl,m);
	if (l> m) return res(l,r,i*2+1,m+1,tr);
    	return fn(res(l,m,i*2,tl,m),res(m+1,r,i*2+1,m+1,tr));
}

void update(int pos,int newval,int i=1,int l=0,int r=n-1)
{
	if (l==r) t[i]=newval;else
	{
		int m=(l+r)/2;
		if (pos<=m) update(pos,newval,i*2,l,m);
		     else update(pos,newval,i*2+1,m+1,r);
		t[i]=fn(t[i*2],t[i*2+1]);
	}
}

int main()
{
	scanf("%d",&n);
	vector<int> b(n);
	for (int i=0;i<n;i++) scanf("%d",&b[i]); 
	for (int i=0;i<n;i++) b[i]--;
	a.resize(n);
	fill(a.begin(),a.end(),0);
	build(a);
	update(b[0],1);
	double left[100001];
	for (int i=1;i<=n-1;i++)
	{
		int v=b[i];
		left[i]=res(v,n-1);
		update(v,1);
	}
	fill(a.begin(),a.end(),0);
	build(a);
	update(b[n-1],1);
	double right[100001];
	for (int i=n-2;i>=0;i--)
	{
		int v=b[i];
		right[i]=res(0,v);
		update(v,1);
	}
	double ans=0;
	for(int i=1;i<n-1;i++) ans+=left[i]*right[i];
	printf("%.0f",ans);
}