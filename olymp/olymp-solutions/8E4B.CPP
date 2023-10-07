#include<iostream>

int rec(int n)
{
	if (n==3) return 1;
	if (n<=4) return 0;
	int x=n>>1;
	int r=0;
	(n&1) ? r+=(rec(x)+rec(x+1)) : r+=(2*rec(x));
	return r;
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n;
	std::cin>>n;
	std::cout<<rec(n);
}