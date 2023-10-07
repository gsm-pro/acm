#include<cmath>
#include<set>
#include<iostream>
using namespace std;
#define EPS 1e-12
#define LD long double
#define sqr(x) (x)*(x)

struct point 
{
	LD x,y;
	point() {}
	point(LD x,LD y) 
	{
		this->x=x;
		this->y=y;
	}
};

struct circle 
{
	LD x,y,r;
	circle() {};
	circle(LD x,LD y,LD r) 
	{
		this->x = x;
		this->y = y;
		this->r = r;
	}
};

struct line 
{
	LD a,b,c;
	line() {};
	line(const point &p1,const point &p2) 
	{
		a=p1.y-p2.y;
		b=p2.x-p1.x;
		c=-(a*p1.x+b*p1.y);
	}
	line(LD a,LD b,LD c) 
	{
		this->a=a;
		this->b=b;
		this->c=c;
	}
};

struct tangent 
{
	line l;
	point p1,p2;
};

LD mod(point p) 
{
	return sqrt(p.x*p.x+p.y*p.y);
};

bool equal(LD a,LD b) 
{
	return fabs(a-b)<EPS;
};

circle c1,c2;
set<tangent> tg;

void norm(line& l) 
{
	LD d=mod(point(l.a,l.b));
	if (equal(d,0)) return;
	l.a/=d;
	l.b/=d;
	l.c/=d;
	if (l.a<0 || (equal(l.a,0) && l.b< 0)) 
	{
		l.a*=-1;
		l.b*=-1;
		l.c*=-1;
	}
	if (l.a==-0) l.a=0;
	if (l.b==-0) l.b=0;
	if (l.c==-0) l.c=0;
}

void getTangents(circle c1,circle c2)
{
	c2.x-=c1.x;
	c2.y-=c1.y;
	LD d=sqr(c2.x)+sqr(c2.y);
	LD c=d-sqr(c2.r-c1.r);
	if (c<-EPS) return;
	c=fabsl(c);
	point v,p1,p2;
	v.x=(c2.x*sqrtl(c)-c2.y*(c2.r-c1.r))/d;
	v.y=(c2.x*(c2.r-c1.r)+c2.y*sqrtl(c))/d;
	p2.x=v.x*sqrtl(c)-v.y*c1.r+c1.x;
	p2.y=v.y*sqrtl(c)+v.x*c1.r+c1.y;
	p1.x=-v.y*c1.r+c1.x;
	p1.y=+v.x*c1.r+c1.y;
	tangent x;
	x.p1=p1;
	x.p2=p2;
	x.l=line(-v.y,v.x,p1.x*v.y-p1.y*v.x);
	norm(x.l);
	tg.insert(x);
}

void tangents(circle c1,circle c2) 
{
	getTangents(c1,c2);
	c1.r*=-1;
	c2.r*=-1;
	getTangents(c1,c2);
	c2.r*=-1;
	getTangents(c1,c2);
	c1.r*=-1;
	c2.r*=-1;
	getTangents(c1,c2);
}

bool operator < (tangent t1,tangent t2)
{
	if ((t1.l.a<t2.l.a) || (t1.l.a==t2.l.a && t1.l.b<t2.l.b) || (t1.l.a==t2.l.a && t1.l.b==t2.l.b && t1.l.c<t2.l.c)) return 1;
	return 0;
}

void solve() 
{
	if (c1.x==c2.x && c1.y==c2.y && c1.r==c2.r)
	{
		cout<<-1<<endl;
		cout<<endl;
		return;
	}
	tangents(c1,c2);
	cout<<(int)tg.size()<<endl;
	set<tangent>::iterator it=tg.begin();
	for (;it!=tg.end();it++)
	{
		tangent q=*it;
		cout<<q.l.a<<" "<<q.l.b<<" "<<q.l.c<<endl;
	}
	cout<<endl;
}

int main() 
{
	cout.precision(20);
	int kol;
	cin>>kol;
	while (kol-->0)
	{
		cin>>c1.x>>c1.y>>c1.r>>c2.x>>c2.y>>c2.r;
		solve();
		tg.clear();
	}
}