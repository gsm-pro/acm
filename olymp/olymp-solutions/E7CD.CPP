#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<map>
using namespace std;
#define INF 1000000
map<string,vector<int>> p;
map<string,int> in;
string z1,z2;
vector<string> ans;
int tm;
_w64 int q;

int toTime(string z)
{
	int r=((z[0]-'0')*10+(z[1]-'0'))*3600;
	r=r+((z[3]-'0')*10+(z[4]-'0'))*60;
	r=r+(z[6]-'0')*10+(z[7]-'0');
	return r;
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n,m;
	cin>>n>>m;
	for (int i=0;i<n;i++)
	{
		cin>>z1>>z2;
		p[z2].push_back(toTime(z1));
		in[z2]++;
	}
	for (map<string,int>::iterator it=in.begin();it!=in.end();it++)
	{
		p[it->first].push_back(-100);
		p[it->first].push_back(-50);
		p[it->first].push_back(INF);
		p[it->first].push_back(INF);
		if (it->second%2==1) p[it->first].push_back(INF);
	}
	for (map<string,vector<int>>::iterator it=p.begin();it!=p.end();it++)
		sort(it->second.begin(),it->second.end());
	for (int i=0;i<m;i++)
	{
		ans.clear();
		cin>>z1;
		tm=toTime(z1);
		for (map<string,vector<int>>::iterator it=p.begin();it!=p.end();it++)
		{
			q=lower_bound(it->second.begin(),it->second.end(),tm)-(it->second.begin());
			if (q&1 && it->second[q-1]<=tm && it->second[q]>=tm) ans.push_back(it->first);else
				if (it->second[q]==tm) ans.push_back(it->first);
		}
		cout<<(int)ans.size()<<" ";
		for (int j=0;j<(int)ans.size();j++) cout<<ans[j]<<" ";
		cout<<endl;
	}
}