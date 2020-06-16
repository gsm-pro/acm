#include<iostream>
#include<vector>
#include<algorithm>
#define LL long long
#define Z 20000000
using namespace std;

bool cmp(pair<pair<LL,LL>,pair<LL,LL>> a,pair<pair<LL,LL>,pair<LL,LL>> b)
{
	if (a.first.first>b.first.first) return 0;
	if (a.first.first==b.first.first && a.first.second<b.first.second)
		return 0;
	return 1;
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n,k;
	cin>>n>>k;
	vector<LL> horses(n),a(k),b(n);
	vector<pair<pair<LL,LL>,pair<LL,LL>>> uch(n);
	for (int i=0;i<n;i++)
	{
		LL a,b,c;
		cin>>a>>b>>c;
		uch[i]=make_pair(make_pair(Z-a,c),make_pair(b,i));
	}
	for (int i=0;i<k;i++) cin>>a[i];
	for (int i=0;i<n;i++) cin>>b[i];
	for (int i=0;i<k;i++)
	{
		for (int j=0;j<n;j++)
			horses[j]=3*a[i]*a[i]+5*a[i]*b[j]+2*b[j]*b[j];
		sort(horses.begin(),horses.end());
		reverse(horses.begin(),horses.end());
		sort(uch.begin(),uch.end(),cmp);
		for (int j=0;j<n;j++)
			uch[j].first.first=uch[j].first.first+Z-uch[j].second.first-horses[j];
	}
	sort(uch.begin(),uch.end(),cmp);
	for (int i=0;i<n;i++) cout<<uch[i].second.second+1<<" ";
}