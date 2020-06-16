#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int n,a,b,q;
vector<int> v;

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>n;
	q=n;
	while (n-->0)
	{
		cin>>a>>b;
		v.push_back(a*3+b);
	}
	sort(v.begin(),v.end());
	cout<<v[q-1]-v[q-2];
}