#include<iostream.h>

int main()
{
	int a,b;
	cin>>a>>b;
	for(;b;b^=a^=b^=a%=b);
	cout<<a;
}