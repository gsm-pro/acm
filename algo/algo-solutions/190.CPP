#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<algorithm>
#define SI string,int
using namespace std;

bool cmp(pair<SI> &a,pair<SI> &b)
{
	if ((a.second>b.second) || (a.second==b.second && a.first<b.first)) return 1;
	return 0;
}

int main()
{
	vector<pair<SI>> v;
	map<SI> a;
	string s;
	while (cin>>s) a[s]++;
	for(map<SI>::iterator it=a.begin();it!=a.end();it++)
		v.push_back(*it);
	sort(v.begin(),v.end(),cmp);
	for (int i=0;i<10;i++) cout<<v[i].first<<" "<<v[i].second<<endl;
}