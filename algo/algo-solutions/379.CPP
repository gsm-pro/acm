#include<iostream>
#include<cmath>
using namespace std;
double a[30],r=1e9,b,w;
int n,i;

int main()
{
	cin>>n;
	for (i=0;i<n;i++) cin>>a[i];
	for (int m=0;m<(1<<n);m++)
	{
		b=w=0;
		for (i=0;i<n;i++) ((m>>i)&1) ? b+=a[i] : w+=a[i];
		r=min(r,fabs(b-w));
	}
	cout<<fixed<<r;
}