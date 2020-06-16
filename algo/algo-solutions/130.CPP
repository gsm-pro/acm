#include<iostream>
#include<cmath>
using namespace std;

int main()
{
	int n,a,lc=0;
	cin>>n;
	for (int i=1;i<=n;i++)
	{
		cin>>a;
		lc=max(lc,i-a);
	}
	cout<<lc+1;
}