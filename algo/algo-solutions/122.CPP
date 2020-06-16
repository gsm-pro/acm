#include<cstdio>
#include<vector>
#include<cmath>
using namespace std;
#define LD long double
#define sqr(x) (x)*(x)
#define PDD pair<LD,LD>

int intersect(LD &x1,LD &y1,LD &r1,LD &x2,LD &y2,LD &r2,vector<PDD>&r)
{
	LD a=x1-x2;
	LD b=y1-y2;
	if (!a && !b)
	{
		if (r1==r2) return -1;
		return 0;
	}
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
	LD sq=sqrt(s/l/l);
	for (int i=1;i<=(s!=0)+1;i++)
	{
		r.push_back(make_pair(-a*c/l-b*sq+x1,-b*c/l+a*sq+y1));
		sq=-sq;
	}
	return (int)r.size();
}

int main()
{
	int k;
	scanf_s("%d",&k);
	while (k-->0)
	{
		LD x1,y1,r1,x2,y2,r2;
		scanf_s("%lf%lf%lf%lf%lf%lf",&x1,&y1,&r1,&x2,&y2,&r2);
		vector<PDD> t;
		int m=intersect(x1,y1,r1,x2,y2,r2,t);
		if (m==0) printf("There are no points!!!\n");
		if (m==-1) printf("I can't count them - too many points :(\n");
		if (m>0)
		{
			printf("There are only %d of them....\n",m);
			for (int i=0;i<m;i++) printf("%.12lf %.12lf\n",t[i].first,t[i].second);
		}
		printf("\n");
	}
}