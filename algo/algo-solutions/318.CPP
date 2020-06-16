#include <string>
#include <iostream>
using namespace std;
int p,n,k;
string s;
bool or();
bool xor();
bool and();
bool unary();

bool or()
{
	bool res=xor();
	while(p<n && s[p]=='|')
	{
		p++;
		res|=xor();
	}
	return res;
}

bool xor()
{
	bool res=and();
	while(p<n && s[p]=='^') 
	{
		p++;
		res^=and();
	}
	return res;
}

bool and()
{
	bool res=unary();
	while(p<n && s[p]=='&')
	{
		p++;
		res&=unary();
	}
	return res;
}

bool unary()
{
	if (s[p]=='1') 
	{
		p++;
		return true;
	}
	if (s[p]=='0')
	{
		p++;
		return false;
	}
	if (s[p]=='!') 
	{
		p++;
		return !unary();
	}
	if (s[p]=='(')
	{
		p++;
		bool res=or();
		p++;
		return res;
	}
	return false;
}

int main()
{
	cin>>k;	
	for(int i=0;i<k;i++)
	{
		cin>>s;
		n=(int)s.length();
		p=0;
		bool res=or();
		if (res==true) cout<<1;else cout<<0;
		cout<<endl;
	}
}