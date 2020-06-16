#define _USE_MATH_DEFINES
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;
#define LD long double
#define sqr(x) (x)*(x)
const LD eps=0.05;
vector< pair<LD,LD> > ans;

struct Point
{
	LD x,y;
	Point() {};
	Point(LD _x,LD _y) {x=_x;y=_y;}
};

Point operator + (const Point &l,const Point &r)
{
	return Point(l.x+r.x,l.y+r.y);
}

Point operator - (const Point &l,const Point &r)
{
	return Point(l.x-r.x,l.y-r.y);
}

Point operator * (const Point &p,LD d) 
{
	return Point(p.x*d,p.y*d);
};

struct Line
{
	LD a,b,c;
	Line() {};
	Line(LD _a,LD _b,LD _c) {a=_a;b=_b;c=_c;}
};

struct Circle
{
	Point c;
	LD r;
	Circle() {};
	Circle(Point _c,LD _r) {c=_c;r=_r;}
};

struct Arch
{
	Point c;
	LD r;
	Point q1,q2,q3;
	Arch() {};
	Arch(Point _c,LD _r,Point _q1,Point _q2,Point _q3) {c=_c;r=_r;q1=_q1;q2=_q2;q3=_q3;}
};

bool Eq(LD x,LD y)
{
	return (fabs(x-y)<eps);
}

LD hyp(LD a,LD b)
{
	return sqrt(a*a+b*b);
}

bool EqPoints(Point p1,Point p2)
{
	return (Eq(p1.x,p2.x) && Eq(p1.y,p2.y));
}

int Sign(LD x)
{
	if (x<0) return -1;
	if (Eq(x,0.0)) return 0;
	return 1;
}

LD Dist(Point &p1,Point &p2)
{
	return hyp(p1.x-p2.x,p1.y-p2.y);
}

void GetLine(Point &p1,Point &p2,Line &l)
{
	l.a=p1.y-p2.y;
	l.b=p2.x-p1.x;
	l.c=-l.a*p1.x-l.b*p1.y;
	LD norm=hyp(l.a,l.b);
	l.a/=norm;
	l.b/=norm;
	l.c/=norm;
}

bool OneSide(Point &p1,Point &p2,Line &l)
{
	return Sign(l.a*p1.x+l.b*p1.y+l.c)*Sign(l.a*p2.x+l.b*p2.y+l.c)>=0;
}

void GetCircle(Point p1,Point p2,Point p3,Circle &res)
{
	if (Eq(p2.x,p1.x)) swap(p1,p3);
	res.c.y=((p3.x-p2.x)*(p2.x*p2.x-p1.x*p1.x+p2.y*p2.y-p1.y*p1.y)-
		(p2.x-p1.x)*(p3.x*p3.x-p2.x*p2.x+p3.y*p3.y-p2.y*p2.y))/(2*
		((p3.x-p2.x)*(p2.y-p1.y)-(p2.x-p1.x)*(p3.y-p2.y)));
	res.c.x=(p2.x*p2.x-p1.x*p1.x+p2.y*p2.y-p1.y*p1.y-2*res.c.y*(p2.y-p1.y))/(2*(p2.x-p1.x));
	res.r=Dist(res.c,p1);
}

bool PointInArch(Point w,Arch A)
{
	Line L;
	GetLine(A.q1,A.q2,L);
	return (Eq(sqr(A.c.x-w.x)+sqr(A.c.y-w.y),A.r*A.r) && OneSide(A.q3,w,L));
}

int InterSect(LD x1,LD y1,LD r1,LD x2,LD y2,LD r2,vector< pair<LD,LD> > &res)
{
	LD a=x1-x2;
	LD b=y1-y2;
	LD l=sqr(a)+sqr(b);
	LD c=sqr(r1)-sqr(r2)+l;
	a+=a;
	b+=b;
	l*=4;
	LD s=sqr(r1)*l-c*c;
	if (s<0) return 0;
	if (b<0 || (b==0 && a>0))
	{
		a=-a;
		b=-b;
		c=-c;
	}
	LD sq=sqrt(s/(l*l));
	for (int i=1;i<=(s!=0)+1;i++)
	{
		res.push_back(make_pair(-a*c/l-b*sq+x1,-b*c/l+a*sq+y1));
		sq=-sq;
	}
	return (int)res.size();
}

void inf()
{
	cout<<"Infinity";
	exit(0);
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n;
	cin>>n;
	LD x1,y1,x2,y2,x3,y3;
	vector<Arch> archs;
	for (int i=0;i<n;i++)
	{
		cin>>x1>>y1>>x2>>y2>>x3>>y3;
		x1=floor(x1*100000);
		y1=floor(y1*100000);
		x2=floor(x2*100000);
		y2=floor(y2*100000);
		x3=floor(x3*100000);
		y3=floor(y3*100000);
		Circle C;
		Point p1(x1,y1);
		Point p2(x2,y2);
		Point p3(x3,y3);
		GetCircle(p1,p2,p3,C);
		Arch A(C.c,C.r,p1,p2,p3);
		archs.push_back(A);
	}
	for (int i=0;i<n;i++)
	{
		for (int j=i+1;j<n;j++)
		{
			vector< pair<LD,LD> > res;
			Arch b1=archs[i];
			Arch b2=archs[j];
			if (EqPoints(b1.q1,b2.q1)) ans.push_back(make_pair(b1.q1.x,b1.q1.y));
			if (EqPoints(b1.q1,b2.q2)) ans.push_back(make_pair(b1.q1.x,b1.q1.y));
			if (EqPoints(b1.q2,b2.q1)) ans.push_back(make_pair(b1.q2.x,b1.q2.y));
			if (EqPoints(b1.q2,b2.q2)) ans.push_back(make_pair(b1.q2.x,b1.q2.y));
			if (Eq(b1.r,b2.r) && EqPoints(b1.c,b2.c))
			{
				Line L;
				if (EqPoints(b1.q1,b2.q1) && EqPoints(b1.q2,b2.q2))
				{
					GetLine(b1.q1,b1.q2,L);
					if (OneSide(b1.q3,b2.q3,L)) inf();else goto LABEL;
				}
				if (EqPoints(b1.q2,b2.q1) && EqPoints(b1.q1,b2.q2))
				{
					GetLine(b2.q1,b2.q2,L);
					if (OneSide(b1.q3,b2.q3,L)) inf();else goto LABEL;
				}
				if (PointInArch(b1.q1,b2) && PointInArch(b2.q1,b1))
				{
					if (EqPoints(b1.q1,b2.q1)) res.push_back(make_pair(b1.q1.x,b1.q1.y));else inf();
				}
				if (PointInArch(b1.q1,b2) && PointInArch(b2.q2,b1))
				{
					if (EqPoints(b1.q1,b2.q2)) res.push_back(make_pair(b1.q1.x,b1.q1.y));else inf();
				}
				if (PointInArch(b1.q2,b2) && PointInArch(b2.q1,b1))
				{
					if (EqPoints(b1.q2,b2.q1)) res.push_back(make_pair(b1.q2.x,b1.q2.y));else inf();
				}
				if (PointInArch(b1.q2,b2) && PointInArch(b2.q2,b1))
				{
					if (EqPoints(b1.q2,b2.q2)) res.push_back(make_pair(b1.q2.x,b1.q2.y));else inf();
				}
LABEL:;
			}			
			InterSect(b1.c.x,b1.c.y,b1.r,b2.c.x,b2.c.y,b2.r,res);
			for (int t=0;t<(int)res.size();t++) 
				if (PointInArch(Point(res[t].first,res[t].second),b1) && 
					PointInArch(Point(res[t].first,res[t].second),b2)) ans.push_back(res[t]);
		}
	}
	sort(ans.begin(),ans.end());
	vector< pair<LD,LD> > ans_tmp;
	if ((int)ans.size()>0)
	{
		ans_tmp.push_back(ans[0]);
		for (int i=1;i<(int)ans.size();i++)
			if (!EqPoints(Point(ans[i-1].first,ans[i-1].second),Point(ans[i].first,ans[i].second)))
				ans_tmp.push_back(ans[i]);
	}
	ans=ans_tmp;
	cout<<(int)ans.size()<<endl;
	cout.precision(5);
	for (int i=0;i<(int)ans.size();i++) 
		cout<<fixed<<ans[i].first/100000.0<<" "<<ans[i].second/100000.0<<endl;
}