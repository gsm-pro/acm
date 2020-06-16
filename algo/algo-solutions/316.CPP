#include<iostream>
#include<string>
using namespace std;
string s;
int p=0;
int A();

int U()
{
	int r;
	if (s[p]=='(')
	{
		p++,r=A(),p++;
		return r;
	}
	r=0;
	while (s[p]>='0') r=r*10+s[p]-'0',p++;
	return r;
}

int M()
{
	int r=U();
	while (s[p]=='*') p++,r*=U();
	return r;
}

int A()
{
	int r=M();
	while (s[p]=='+' || s[p]=='-')
	{
		p++;
		(s[p-1]=='+') ? r+=M() : r-=M();
	}
	return r;
}

int main()
{
	cin>>s;
	cout<<A();
}