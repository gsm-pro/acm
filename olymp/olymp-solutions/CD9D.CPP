#include<iostream>
#include<string>
using namespace std;

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n;
	string s="";
	cin>>n;
	for (int i=31;i>=0;i--) s+=((n>>i)&1) ? "1" : "0";
	while (s!="" && s[0]=='0') s.erase(0,1);
	(s=="") ? cout<<"0" : cout<<s;
}