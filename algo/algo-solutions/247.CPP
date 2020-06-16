#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
#define LD long double

struct segm 
{
	int x1,y1,x2,y2;
};

struct point 
{
	LD x,y;
};

struct item 
{
	LD y1,y2;
	int tr_id;
};

struct line 
{
	int a,b,c;
};

const LD EPS=1E-9;

void intersect(segm s1,segm s2,vector<point> &res) 
{
	line l1={s1.y1-s1.y2,s1.x2-s1.x1,l1.a*s1.x1+l1.b*s1.y1};
	line l2={s2.y1-s2.y2,s2.x2-s2.x1,l2.a*s2.x1+l2.b*s2.y1};
	LD det1=l1.a*l2.b-l1.b*l2.a;
	if (abs(det1)<EPS) return;
	point p={(l1.c*1.0*l2.b-l1.b*1.0*l2.c)/det1,(l1.a*1.0*l2.c-l1.c*1.0*l2.a)/det1};
	if (p.x>=s1.x1-EPS && p.x<=s1.x2+EPS && p.x>=s2.x1-EPS && p.x<=s2.x2+EPS) res.push_back(p);
}

LD segm_y(segm s,LD x) 
{
	return s.y1+(s.y2-s.y1)*(x-s.x1)/(s.x2-s.x1);
}

bool eq(LD a,LD b) 
{
	return abs(a-b)<EPS;
}

vector<item> c;

bool cmp(int i,int j) 
{
	const item &a=c[i];
	const item &b=c[j];
	return a.y1<b.y1-EPS || abs(a.y1-b.y1)<EPS && a.y2<b.y2-EPS;
}

int main() 
{
	int n;
	cin>>n;
	vector<segm> a(n*3);
	for (int i=0;i<n;i++) 
	{
		int x1,y1,x2,y2,x3,y3;
		cin>>x1>>y1>>x2>>y2>>x3>>y3;
		segm s1={x1,y1,x2,y2};
		segm s2={x1,y1,x3,y3};
		segm s3={x2,y2,x3,y3};
		a[i*3]=s1;
		a[i*3+1]=s2;
		a[i*3+2]=s3;
	}
	for (int i=0;i<(int)a.size();i++)
		if (a[i].x1>a[i].x2) swap(a[i].x1,a[i].x2),swap(a[i].y1,a[i].y2);
	vector<point> b;
	b.reserve(n*n*3);
	for (int i=0;i<(int)a.size();i++)
		for (int j=i+1;j<(int)a.size();++j) intersect(a[i],a[j],b);
	vector<LD> xs(b.size());
	for (int i=0;i<(int)b.size();i++) xs[i]=b[i].x;
	sort(xs.begin(),xs.end());
	xs.erase(unique(xs.begin(),xs.end(),&eq),xs.end());
	LD res=0;
	vector<char> used(n);
	vector<int> cc(n*3);
	c.resize(n*3);
	for (int i=0;i+1<(int)xs.size();i++) 
	{
		LD x1=xs[i],x2=xs[i+1];
		int csz=0;
		for (int j=0;j<(int)a.size();j++)
			if (a[j].x1!=a[j].x2)
				if (a[j].x1<=x1+EPS && a[j].x2>=x2-EPS) 
				{
					item it={segm_y(a[j],x1),segm_y(a[j],x2),(int)j/3};
					cc[csz]=(int)csz;
					c[csz++]=it;
				}
				sort(cc.begin(),cc.begin()+csz,&cmp);
				LD add_res=0;
				for (int j=0;j<csz;) 
				{
					item lower=c[cc[j++]];
					used[lower.tr_id]=true;
					int cnt=1;
					while (cnt && j<csz) 
					{
						char &cur=used[c[cc[j++]].tr_id];
						cur=!cur;
						if (cur) cnt++;else cnt--;
					}
					item upper=c[cc[j-1]];
					add_res+=upper.y1-lower.y1+upper.y2-lower.y2;
				}
				res+=add_res*(x2-x1)/2;
	}
	cout.precision(9);
	cout<<fixed<<res;
}