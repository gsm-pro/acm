#include<iostream>
#include<string>
using namespace std;
int cnt[10]={},tt[10]={};

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	string t,x;
	cin>>t>>x;
	for (int i=0;i<(int)t.size();i++) tt[t[i]-'0']++;
	for (int i=0;i<(int)x.size();i++) cnt[x[i]-'0']++;
	tt[2]+=tt[5];
	cnt[2]+=cnt[5];
	tt[6]+=tt[9];
	cnt[6]+=cnt[9];
	int ans=(1<<20);
	for (int i=0;i<10;i++) 
		if (i!=5 && i!=9 && tt[i]!=0) ans=min(ans,cnt[i]/tt[i]);
	cout<<ans;
}