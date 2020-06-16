#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n,i=0;
	string s;
	cin>>n;
	vector<pair<int,string>> a(n);
	while (n-->0) cin>>a[i].second>>a[i].first,i++;
	sort(a.begin(),a.end());
	for (int j=0;j<i;j++) cout<<a[j].second<<endl;
}