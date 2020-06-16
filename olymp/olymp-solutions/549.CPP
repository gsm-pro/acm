#include<iostream>
#include<string>
using namespace std;

int f(string s)
{
	if (s=="Monday") return 1;
	if (s=="Tuesday") return 2;
	if (s=="Wednesday") return 3;
	if (s=="Thursday") return 4;
	if (s=="Friday") return 5;
	if (s=="Saturday") return 6;
	if (s=="Sunday") return 7;
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	string a,b;
	cin>>a>>b;
	int x=(f(b)-f(a)+7)%7;
	if (x==0) x=7;
	cout<<x;
}