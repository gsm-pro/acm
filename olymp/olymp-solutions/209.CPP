#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int n,x;
vector<int> a,b;

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>n;
	while (n-->0)
	{
		cin>>x;
		if (x&1) a.push_back(x);else b.push_back(x);
	}
	sort(a.begin(),a.end());
	sort(b.begin(),b.end());
	reverse(b.begin(),b.end());
	for (int i=0;i<(int)a.size();i++) cout<<a[i]<<" ";
	for (int i=0;i<(int)b.size();i++) cout<<b[i]<<" ";
}