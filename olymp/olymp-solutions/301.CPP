#include<vector>
#include<iostream>
#include<string>
using namespace std;
__int64 e[18]={1};

__int64 toDec(string x)
{
	__int64 a=0;
	for (int i=0;i<(int)x.size();i++)
	{
		int r;
		if (x[i]=='X') r=10;else r=x[i]-'0';
		a+=(r*e[(int)x.size()-1-i]);
	}
	return a;
}

string toBer(__int64 a)
{
	string x="";
	for (int i=17;i>=0;i--)
	{
		int r=(int)(a/e[i]);
		a-=(r*e[i]);
		if (r==10) x+="X";else x+=(r+'0');
	}
	while (x[0]=='0') x.erase(0,1);
	return x;
}


int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	__int64 p=10;
	for (int i=1;i<18;i++)
	{
		e[i]=p+e[i-1];
		p*=10;
	}
	string a,b;
	cin>>a>>b;
	__int64 v=toDec(a)*toDec(b);
	cout<<toBer(v);
}