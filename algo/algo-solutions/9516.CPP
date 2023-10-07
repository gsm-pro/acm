#include<iostream>
#include<set>
using namespace std;

int main()
{
	int k,x,n;
	multiset<int> a;
	cin>>n>>k;
	for (int i=1;i<=k;i++)
	{
		cin>>x;
		a.insert(x);
	}
	for (int i=k+1;i<=n;i++)
	{
		cin>>x;
		if (x<*(--a.end())) 
		{
			a.erase(--a.end());
			a.insert(x);
		}
	}
	cout<<*(--a.end());
}