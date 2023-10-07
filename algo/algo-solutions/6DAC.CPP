#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct point {
	int x,y;
};

bool cmp(point a,point b) {
	return a.x<b.x || a.x==b.x && a.y<b.y;
}

bool cw(point a,point b,point c) {
	return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y)<0;
}

bool ccw(point a,point b,point c) {
	return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y)>0;
}

void convex_hull(vector<point> &a) {
	if (a.size()==1) return;
	sort(a.begin(),a.end(),&cmp);
	point p1=a[0],p2=a.back();
	vector<point> up,down;
	up.push_back(p1);
	down.push_back(p1);
	for (int i=1;i<(int)a.size();i++) {
		if (i==a.size()-1 || cw(p1,a[i],p2)) {
			while (up.size()>=2 && !cw(up[up.size()-2],up[up.size()-1],a[i])) up.pop_back();
			up.push_back(a[i]);
		}
		if (i==a.size()-1 || ccw(p1,a[i],p2)) {
			while (down.size()>=2 && !ccw(down[down.size()-2],down[down.size()-1],a[i])) down.pop_back();
			down.push_back(a[i]);
		}
	}
	a.clear();
	for (int i=0;i<(int)up.size();i++) a.push_back(up[i]);
	for (int i=(int)down.size()-2;i>0;i--) a.push_back(down[i]);
}

int main()
{
	int n;
	scanf("%d",&n);
	vector<point> pts(n);
	for (int i=0;i<n;i++) scanf("%d%d",&pts[i].x,&pts[i].y);
	convex_hull(pts);
	pts.push_back(pts[0]);
	long long sq=0;
	for (int i=0;i<(int)pts.size()-1;i++)
		sq=sq+(pts[i+1].x-pts[i].x)*(pts[i+1].y+pts[i].y);
	if (sq>0) reverse(pts.begin(),pts.end());
	pts.pop_back();
	int startIndex=0;
	for (int i=1;i<(int)pts.size();i++)
		if (pts[i].y<pts[startIndex].y || (pts[i].y==pts[startIndex].y && pts[i].x<pts[startIndex].x))
			startIndex=i;
	for (int i=0;i<startIndex;i++) pts.push_back(pts[i]);
	for (int i=0;i<startIndex;i++) pts.erase(pts.begin());
	printf("%d\n",(int)pts.size());
	for (int i=0;i<(int)pts.size();i++) printf("%d %d\n",pts[i].x,pts[i].y);
}