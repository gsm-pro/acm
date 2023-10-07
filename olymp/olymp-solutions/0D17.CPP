#define _USE_MATH_DEFINES
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
#define LD long double
#define pt pair<LD,LD>
#define mp make_pair
#define x first
#define y second
#define pi M_PI
vector<pt> c(1);
pt pt1,pt2;
LD e,ans,r,d_alpha;
int n;

LD dst(pt a,pt b)
{
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

LD vect(pt a,pt b,pt c)
{
	return (b.x-a.x)*(c.y-a.y)-(c.x-a.x)*(b.y-a.y);
}

int cross(pt a,pt b,pt c,pt d)
{
	if (
	   max(a.x,b.x)<min(c.x,d.x) ||
	   min(a.x,b.x)>max(c.x,d.x) ||
	   max(a.y,b.y)<min(c.y,d.y) ||
	   min(a.y,b.y)>max(c.y,d.y)
	   ) return 0;
	if (
	   (vect(a,b,c)*vect(a,b,d))<=0 &&
	   (vect(c,d,a)*vect(c,d,b))<=0
	   ) return 1;
	return 0;
}

int check(pt p,pt q)
{
	int cnt=0;
	for (int i=0;i<n;i++)
		cnt+=cross(p,q,c[i],c[(i+1)%n]);
	return cnt;
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>n>>c[0].x>>c[0].y>>pt1.x>>pt1.y>>pt2.x>>pt2.y;
	r=dst(c[0],mp(0.0,0.0));
	d_alpha=(2.0*pi)/(n+.0);
	for (int i=1;i<n;i++)
	{
		LD ang=atan2(c[i-1].y,c[i-1].x);
		ang+=d_alpha;
		c.push_back(mp(cos(ang)*r,sin(ang)*r));
	}
	e=dst(c[0],c[1]),ans=1e9;
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			if (check(c[i],pt1)==2 && check(c[j],pt2)==2)
			{
				int t=max(i,j)-min(i,j),w=min(t,n-t);
				ans=min(ans,e*w+dst(c[i],pt1)+dst(c[j],pt2));
			}
	if (check(pt1,pt2)==0) ans=dst(pt1,pt2);
	cout.precision(2);
	cout<<fixed<<ans;
}