#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

void main()
{
	int n,a,b;
	cin>>n;
	vector<pair<pair<int,int>,int>> v;
	for (int i=0;i<n;i++) cin>>a>>b,v.push_back(make_pair(make_pair(a,b),i+1));
	sort(v.begin(),v.end());
	for (int i=0;i<n;i++) cout<<v[i].second<<" ";
}