#include<iostream>
using namespace std;
int n,q,k=0,x,r[2001]={};

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>n>>q;
	while (n-->0)
	{
		cin>>x;
		r[x]++;
	}
	for (int i=1;i<=q/2;i++)
		if (2*i!=q) k+=min(r[i],r[q-i]);else k+=r[q/2]/2;
	cout<<k;
}