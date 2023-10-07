#include<iostream>
#include<string>
using namespace std;
int l1,l2;
string z[101][101],s,t;

string rec(int p1,int p2)
{
	string v="",w="";
	if (p1>=l1 && p2>=l2) return "";
	if (z[p1][p2]!="$") return z[p1][p2];
	if (p1<l1) v=s[p1]+rec(p1+1,p2);
	if (p2<l2) w=t[p2]+rec(p1,p2+1);
	if (v>w) 
	{
		z[p1][p2]=v;
		return v;
	}
	z[p1][p2]=w;
	return w;
}

int main() 
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>s>>t;
	l1=(int)s.length();
	l2=(int)t.length();
	for (int i=0;i<=l1;i++)
		for (int j=0;j<=l2;j++) z[i][j]="$";
	cout<<rec(0,0);
}