#include<iostream>
#include<string>
using namespace std;

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	string a,b,c="";
	cin>>a>>b;
	int aa=(int)a.size();
	int bb=(int)b.size();
	for (int i=0;i<9-aa;i++) a="0"+a;
	for (int i=0;i<9-bb;i++) b="0"+b;
	int carry=0,c1,c2,cc;
	for (int i=8;i>0;i--)
	{
		c1=a[i]-'0';
		c2=b[i]-'0';
		cc=c1+c2+carry;
		carry=(cc>1);
		c=char(cc%2+48)+c;
	}
	while (c!="" && c[0]=='0') c=c.erase(0,1);
	if (c=="") c="0";
	cout<<c;
}