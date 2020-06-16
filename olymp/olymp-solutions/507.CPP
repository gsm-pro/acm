#include<fstream>
#include<iostream>
using namespace std;

int main()
{
	ifstream cin("input.txt");
	ofstream cout("output.txt");
	int n,s=0,a[6000],ans=0;
	cin>>n;
	for (int i=0;i<n;i++) 
	{
		cin>>a[i];
		s+=a[i];
	}
	for (int i=1;i<n;i++) a[i]+=a[i-1];
	for (int i=0;i<n;i++) ans=max(ans,abs(a[i]-(s/n)*(i+1)));
	if (s%n!=0) ans=-1;
	cout<<ans;
}