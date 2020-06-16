#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<pair<int,int>> a;
int n,ans=1;
vector<int> d(1001),prev_d(1001);

bool cmp(pair<int,int> a,pair<int,int> b)
{
	return a.first+a.second>b.first+b.second;
}

int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	cin>>n;
	a.resize(n);
	for (int i=0;i<n;i++) cin>>a[i].first>>a[i].second;
	sort(a.begin(),a.end(),cmp);
	for (int i=0;i<n;i++)
	{
		d.assign(1001,0);
		for (int j=0;j<1001;j++)
		{
			d[j]=max(prev_d[j],d[j]);
			if (a[i].first<=j)
			{
				int next_j=prev_d[j] ? min(a[i].second,j-a[i].first) : a[i].second;
				d[next_j]=max(d[next_j],prev_d[j]+1);
			}
		}
		prev_d=d;
	}
	for (int i=0;i<1001;i++) ans=max(ans,d[i]);
	cout<<ans;
}