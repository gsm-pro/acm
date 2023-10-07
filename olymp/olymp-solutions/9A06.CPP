#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define LL long long
#define INF 1LL<<60
#define PREV(x) (x&(x-1))
#define NEXT(X) ((x<<1)-PREV(x))
vector<int> x;

class Tree
{
public:
	vector<LL> a,l,r;
	int n;

	LL getMin(int lf,int rg)
	{
		LL v=INF;
		int x;
		for (x=lf+1;NEXT(x)<=rg+1;x=NEXT(x)) v=min(v,r[x]);
		v=min(v,a[x]);
		for (x=rg+1;PREV(x)>=lf+1;x=PREV(x)) v=min(v,l[x]);
		return v;
	}

	void update(int pos,LL val)
	{
		a[pos+1]=min(a[pos+1],val);
		int x;
		for (x=pos+1;x<=n;x=NEXT(x)) l[x]=min(l[x],val);
		for (x=pos+1;x;x=PREV(x)) r[x]=min(r[x],val);
	}

	Tree(int N)
	{
		n=N;
		a.resize(N+1);
		l.resize(N+1);
		r.resize(N+1);
		for (int i=0;i<=n;i++) a[i]=l[i]=r[i]=INF;
	}
};

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n;
	cin>>n;
	vector<int> pts(n);
	for (int i=0;i<n;i++)
	{
		cin>>pts[i];
		x.push_back(pts[i]);
	}
	x.push_back(0);
	sort(x.begin(),x.end());
	x.resize(unique(x.begin(),x.end())-x.begin());
	int m=(int)x.size();
	int x0=lower_bound(x.begin(),x.end(),0)-x.begin();
	LL res=0;
	Tree left(m),right(m);
	left.update(x0,0);
	right.update(x0,0);
	int curx=0;
	for (int i=0;i<n;i++)
	{
		int x1=lower_bound(x.begin(),x.end(),pts[i])-x.begin();
		LL value=min(left.getMin(0,x1)+pts[i],right.getMin(x1,m-1)-pts[i])-abs(pts[i]-curx);
		left.update(x0,value-curx);
		right.update(x0,value+curx);
		res+=abs(pts[i]-curx);
		curx=pts[i];
		x0=x1;
	}
	LL r=INF;
	for (int i=1;i<=m;i++)
		r=min(r,res+left.a[i]+x[i-1]);
	cout<<r;
}