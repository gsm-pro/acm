#include <iostream>
#include <string>
#include <cmath>
using namespace std;
size_t p,n,k;
string s,t;
double val[26];
double add();
double mult();
double unary();

void error()
{
	cout<<"Error";
	exit(0);
}

double add()
{
	double res=mult();
	while (p<n && (s[p]=='+' || s[p]=='-'))
	{
		char c=s[p++];
		double tmp=mult();
		if (c=='+') res+=tmp;else res-=tmp;
	}
	return res;
}

double mult()
{
	double res=unary();
	while (p<n && (s[p]=='*' || s[p]=='/'))
	{
		char c=s[p++];
		double tmp=unary();
		if (c=='*') res*=tmp;else
		{
			if (fabs(tmp)==0) error();
			res/=tmp;
		}
	}
	return res;
}

double unary()
{
	if (s[p]<='z' && s[p]>='a') return val[s[p++]-'a'];
	if (s[p]<='9' && s[p]>='0')
	{
		double res=0;
		while (p<n && s[p]<='9' && s[p]>='0') res=res*10+s[(p++)]-'0';
		if (s[p]=='.')
		{
			int k=10;
			p++;
			while (p<n && s[p]<='9' && s[p]>='0')
			{
				res=res+double(s[(p++)]-'0')/double(k);
				k*=10;
			}	
		}
		return res;
	}
	if (s[p]=='-')
	{
		p++;
		return -unary();
	}
	if (s[p]=='(')
	{
		p++;
		double res=add();
		p++;
		return res;
	}
	if (s[p]=='S')
	{
		p+=3;
		return sin(unary());
	}
	if (s[p]=='C')
	{
		p+=3;
		return cos(unary());
	}
	if (s[p]=='A')
	{
		p+=3;
		return fabs(unary());
	}
	if (s[p]=='L')
	{
		p+=2;
		double tmp=unary();
		if (tmp<=0) error();
		return log(tmp);
	}
	if (s[p]=='E')
	{
		p+=3;
		return exp(unary());
	}
	return 0;
}

int main()
{
    	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	memset(val,0,sizeof(val));
	cin>>k;
	while (k-->0)
	{
		cin>>s;
		p=2;
		n=s.length();
		val[s[0]-'a']=unary();
	}
	p=0;
	s="";
	while (cin>>t) s+=t;
	n=s.length();
	double ans=add();
	cout.precision(2);
	if (ans > 1e9)
	{
		ans = 1e9;
	}
	cout<<fixed<<ans;
}