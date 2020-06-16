#include<iostream>
#include<cmath>
using namespace std;
#define LD long double

LD biss(LD x2,LD y1,LD x3)
{
	LD u=(atan2(-y1,x2)+atan2(-y1,x3))/2;
	LD a=sin(u);
	LD c=cos(u)*y1;
	return -c/a;
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	LD h,l,m,xh,xl,xm;
	cin>>h>>l>>m;
	xh=0;
	xl=sqrt(l*l-h*h);
	xm=sqrt(m*m-h*h);
	LD xc,xb=-100.0000,step=1.0000;
	bool ok=false;
	int iters=0;
	while (iters<=5000)
	{
		xc=2*xm-xb;
		LD xe=biss(xb,h,xc);
		if (fabs(xl-xe)<1e-9)
		{
			ok=true;
			break;
		}
		if (xe>xl) 
		{
			xb-=step;
			step/=2;
		} else xb+=step;
		iters++;
	}
	if (ok)
	{
		cout.precision(12);
		xc=2*xm-xb;
		cout<<"YES"<<endl;
		cout<<fixed<<0<<" "<<h<<endl<<xb<<" "<<0<<endl<<xc<<" "<<0<<endl;
	} else cout<<"NO"<<endl;
}