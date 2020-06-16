#include<iostream>
#include<string>
using namespace std;

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n,m;
	cin>>n>>m;
	double k=(n+.0)/(m+.0);
	string s="";
	for (int i=0;i<=2*n;i++) s+="1";
	double r=0;
	for (int i=1;i<=2*n;i++)
	{
		r+=k;
		s[(int)(r+0.5)]='0';
		if (r>n) break;
	}
	for (int i=1;i<=n;i++) cout<<s[i];
}