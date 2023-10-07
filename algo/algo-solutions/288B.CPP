#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;
#define MAXN 100001

struct pt 
{
	double x,y;
	int id;
};

inline bool cmp_x(const pt &a,const pt &b)
{
	return a.x<b.x || (a.x==b.x && a.y<b.y);
}

inline bool cmp_y(const pt &a,const pt &b)
{
	return a.y<b.y;
}

pt a[MAXN];
double mindist;
int ans1,ans2;

inline void check(const pt &a,const pt &b)
{
	double dist=sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
	if (dist<mindist) mindist=dist,ans1=a.id,ans2=b.id;
}

void rec(int l,int r)
{
	if (r-l<=3)
	{
		for (int i=l;i<=r;++i)
			for (int j=i+1;j<=r;++j) check(a[i],a[j]);
		sort(a+l,a+r+1,&cmp_y);
		return;
	}
	int m=(l+r)>>1;
	double midx=a[m].x;
	rec(l,m);
	rec(m+1,r);
	inplace_merge(a+l,a+m+1,a+r+1,&cmp_y);
	static pt t[MAXN];
	int t_size=0;
	for (int i=l;i<=r;++i)
	{
		if (abs(a[i].x-midx)<mindist)
		{
			for (int j=t_size-1;j>=0 && a[i].y-t[j].y<mindist;--j)
				check(a[i],t[j]);
			t[t_size++]=a[i];
		}
	}
}

int main()
{
	int n;
	while (scanf("%d",&n)==1)
	{
		for (int i=0;i<n;i++)
		{
			scanf("%lf%lf",&a[i].x,&a[i].y);
			a[i].id=i;
		}
		sort(a,a+n,&cmp_x);
		mindist=1e20;
		rec(0,n-1);
		printf("%d %d\n",min(ans1,ans2)+1,max(ans1,ans2)+1);
	}
}