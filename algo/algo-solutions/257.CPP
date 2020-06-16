#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

bool mod_lesser_ex(pair<int,string> a,pair<int,string> b)
{
	return abs(a.first)<abs(b.first);
}

int main()
{
	int n;
	cin>>n;
	vector<pair<int,string>> b(n);
	for (int i=0;i<n;i++) cin>>b[i].second>>b[i].first;
	stable_sort(b.begin(),b.end(),mod_lesser_ex);
	for (int i=0;i<(int)b.size();i++) cout<<b[i].second<<" "<<b[i].first<<endl;
}