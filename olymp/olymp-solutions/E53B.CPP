#include<iostream>
using namespace std;
char s[100001];
int len[100001];
long long ans=0;

int main() 
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	gets(s);
	int n=(int)strlen(s),l=0,r=0;
	memset(len,0,sizeof(len));
	for (int i=0;i<n-1;++i)
	{
		if (i<=r) len[i]=min(len[l+r-i],r-i+1);else len[i]=1;
		while (i+len[i]<n && i-len[i]>=0 && s[i+len[i]]==s[i-len[i]]) ++len[i];
		if (i+len[i]-1>r) l=i-len[i]+1,r=i+len[i]-1;
		ans+=len[i]-1;
	}    
	memset(len,0,sizeof(len));
	l=0,r=0;
	for (int i=0;i<n-1;++i) 
	{
		if (s[i]!=s[i+1]) continue;
		if (i<r) len[i]=min(len[l+r-i-1],r-i);else len[i]=1;
		while (i+len[i]+1<n && i-len[i]>=0 && s[i+len[i]+1]==s[i-len[i]]) ++len[i];
		if (i+len[i]>r) l=i-len[i]+1,r=i+len[i];
		ans+=len[i];
	}    
	cout<<ans;
}