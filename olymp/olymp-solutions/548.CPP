#include<iostream>
using namespace std;

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int t,d,m,k=0;
	cin>>t>>d>>m;
	for (int i=t;i<=m;i+=d,k++);
	cout<<k;
}