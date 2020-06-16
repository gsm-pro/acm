#include<iostream>
using namespace std;
int n,a,b,k=0;

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>n;
	while (n-->0)
	{
		cin>>a>>b;
		if (((a&1)^(b&1))==0) ++k;
	}
	cout<<k;
}