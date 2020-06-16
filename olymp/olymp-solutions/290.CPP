#include<map>
#include<iostream>
using namespace std;

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	map<int,int> m;
	map<int,int>::iterator it;
	for (int i=0;i<4;i++)
	{
		int x;
		cin>>x;
		m[x]++;
	}
	int ans=0;
	for (it=m.begin();it!=m.end();it++)
		ans+=(it->second)/2;
	cout<<ans;
}