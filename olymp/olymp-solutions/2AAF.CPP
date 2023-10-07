#include<iostream>
#include<vector>
#include<string>
using namespace std;
int cnt[15];
#define has(m,i) (int)((((m)>>(i))&1)==1)
vector<string> ans;

int toNum(char c)
{
	if (c=='T') return 10;
	if (c=='J') return 11;
	if (c=='Q') return 12;
	if (c=='K') return 13;
	if (c=='A') return 14;
	return c-'0';
}

bool street(int m)
{
	if (has(m,0) && has(m,1) && has(m,2) && has(m,3) && has(m,12) && 
			cnt[2]*cnt[3]*cnt[4]*cnt[5]*cnt[14]>0) return true;
	for (int i=0;i<=8;i++)
		if (has(m,i) && has(m,i+1) && has(m,i+2) && has(m,i+3) && has(m,i+4) && 
			cnt[i+2]*cnt[i+3]*cnt[i+4]*cnt[i+5]*cnt[i+6]>0) return true;
	return false;
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n,m1=0,maxCd=0,bestmask=0;
	cin>>n;
	vector<pair<int,string>> cd(n);
	for (int i=0;i<n;i++)
	{
		cin>>cd[i].second;
		cd[i].first=toNum(cd[i].second[0]);
		cnt[cd[i].first]++;
		m1|=(1<<(cd[i].first-2));
	}
	if (!street(m1))
	{
		cout<<-1;
		return 0;
	}
	for (int m=1;m<=(1<<14)-1;m++)
	{
		int kol1=0;
		for (int i=0;i<=12;i++) kol1+=has(m,i)*cnt[i+2];
		if (!street(m))
			if (kol1>maxCd) maxCd=kol1,bestmask=m;
	}
	for (int i=0;i<n;i++)
		if (has(bestmask,cd[i].first-2))
		{
			ans.push_back(cd[i].second);
			cd[i].first=-1;
		}
	for (int i=0;i<n;i++)
		if (cd[i].first!=-1)
		{
			ans.push_back(cd[i].second);
			break;
		}
	cout<<(int)ans.size()<<endl;
	for (int i=0;i<(int)ans.size();i++) cout<<ans[i]<<endl;
}