#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;
int n,d,x,ptr=0,ans=0;
vector<pair<int,int>> a;
vector<int> res;

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>n>>d;
	for (int i=0;i<n;i++)
	{
		cin>>x;
		a.push_back(make_pair(x,i));
	}
	sort(a.begin(),a.end());
	for (int i=0;i<n;i++)
	{
		while (ptr<(int)a.size() && a[ptr].first-a[i].first<=d) ++ptr;
		ans=max(ans,ptr-i);
	}
	cout<<ans<<endl;
	res.resize(n);
	for (int i=0;i<n;i++) res[a[i].second]=i%ans+1;
	for (int i=0;i<n;i++) cout<<res[i]<<" ";
}