#include<iostream>
#include<string>
using namespace std;
int n,m,p=0,x=0,y=0;
int a[11][11];
string s;

int main()
{  
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	cin>>n>>m;
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<m;j++)
		{
			p++;
			a[i][j]=p;
		}
	}
	cin>>s;
	for (int i=0;i<(int)s.length();i++)
	{
		if (s[i]=='L') y=(y-1+m)%m;
		if (s[i]=='R') y=(y+1)%m;
		if (s[i]=='U') x=(x-1+n)%n;
		if (s[i]=='D') x=(x+1)%n;
		if (s[i]=='P') cout<<a[x][y]<<endl;
	}
}