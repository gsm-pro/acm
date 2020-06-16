#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
vector<pair<int,int>> dv;

bool cmp(pair<int,int> a,pair<int,int> b)
{
	if (a.first>b.first || (a.first==b.first && a.second<b.second))
		return 1;
	return 0;
}

int divCnt(int x)
{
	int c=0,i;
	for (i=2;i*i<x;i++) if (x%i==0) ++c;
	return (c<<1)+(i*i==x)+(x>1)+1;
}

int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	int n,m,r=0;
	cin>>n>>m;
	for (int i=1;i<=n;i++) dv.push_back(make_pair(divCnt(i),i));
	sort(dv.begin(),dv.end(),cmp);
	for (int i=0;i<m;i++) r+=dv[i].second;
	cout<<r;
}