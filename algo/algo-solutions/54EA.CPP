#include<iostream>
#include<string>
using namespace std;

string next(string s)
{
	int n=(int)s.length();
	string ans="0";
	for (int i=n-1,c1=0,c2=0;i>=0;--i)
	{
		if (s[i]=='(') ++c1;else ++c2;
		if (s[i]=='(' && c1<c2)
		{
			ans=s.substr(0,i)+')';
			for (int k=0;k<c1;++k) ans+='(';
			for (int k=0;k<c2-1;++k) ans+=')';
			break;
		}
	}
	return ans;
}

int main()
{
	int n;
	cin>>n;
    	string s;
	s="";
	for (int i=0;i<n;i++) s+="(";
	for (int i=0;i<n;i++) s+=")";
	while (s!="0") 
	{
		cout<<s<<endl;
		s=next(s);
	}
}