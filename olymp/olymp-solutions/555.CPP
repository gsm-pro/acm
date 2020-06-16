#include<iostream>
#include<string>
#include<cmath>
using namespace std;
double b[4]={};

bool eq(double a,double b)
{
	return (fabs(a-b)<1e-6);
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>b[0]>>b[1]>>b[2]>>b[3];
	double r1=b[1]-b[0],r2=b[2]-b[1],r3=b[3]-b[2];
	if (r1==r2 && r2==r3)
	{
		cout<<b[3]+r3;
		return 0;
	}
	double q1=1e9,q2=2e9,q3=3e9;
	if (b[0]!=0) q1=b[1]/b[0];
	if (b[1]!=0) q2=b[2]/b[1];
	if (b[2]!=0) q3=b[3]/b[2];
	if (b[3]!=0 && eq(q1,q2) && eq(q2,q3) && eq(b[3]*q3,(int)(b[3]*q3)))
	{
		cout<<(int)b[3]*q3;
		return 0;
	}
	cout<<42;
}