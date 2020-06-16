#include<iostream>
#include<algorithm>
using namespace std;

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n,a[51],s=0;
	cin>>n;
	for (int i=0;i<n;i++) cin>>a[i];
	sort(a,a+n);
	for (int i=0;i<n;i++)
		if ((i+1)%2==0) s+=a[i];else s-=a[i];
	cout<<abs(s);
}