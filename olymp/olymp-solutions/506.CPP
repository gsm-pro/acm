#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int n,x;
vector<int> v;

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>n;
	for (int i=0;i<n;i++)
	{
		cin>>x;
		v.push_back(x);
	}
	sort(v.begin(),v.end());
	for (int i=n-1;i>=0;i--)
	{
		int s=0;
		for (int j=0;j<=i-1;j++) s+=v[j];
		if (v[i]<s)
		{
			cout<<n-1-i;
			return 0;
		}
	}
	cout<<-1;
}