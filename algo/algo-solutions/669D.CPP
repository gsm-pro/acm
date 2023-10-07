#include<string>
#include<iostream>
#include<set>
using namespace std;
#define LL long long
LL HS[100002],PW[100002];
set<LL> was;

int main()
{
	string s;
	cin>>s;
	int k,l,r,n=(int)s.length();
	PW[0]=1;
	for (int i=1;i<=n;i++) PW[i]=PW[i-1]*511;
	HS[0]=0;
	for (int i=0;i<=n;i++) HS[i+1]=HS[i]+s[i]*PW[i];
	cin>>k;
	while (k-->0)
	{
		cin>>l>>r;
		was.insert((HS[r]-HS[l-1])*PW[n-l]);
	}
	cout<<(int)was.size();
}