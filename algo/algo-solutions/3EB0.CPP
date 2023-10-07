#include<cstdio>
#include<cmath>
using namespace std;

int main()
{
	int n,i;
	scanf_s("%d",&n);
	int x[100001],y[100001];
	for (i=0;i<n;i++) scanf_s("%d%d",&x[i],&y[i]);
	x[n]=x[0];
	y[n]=y[0];
	double s1=0,s2=0;
	for (i=0;i<n;i++) 
	{
		s1+=0.5*(x[i+1]-x[i])*(y[i+1]+y[i]);
		s2+=0.5*abs((x[i]-x[0])*(y[i+1]-y[0])-(x[i+1]-x[0])*(y[i]-y[0]));
	}
	(abs(s2-abs(s1))<1e-5) ? puts("YES") : puts("NO");
}