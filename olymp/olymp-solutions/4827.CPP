#include<iostream>
#include<string>
using namespace std;
int page[200]={},c[200]={};

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n,k,m;
	cin>>n>>k>>m;
	for (int i=0;i<200;i++) page[i]=1;
	for (int i=0;i<m;i++)
	{
		int x;
		cin>>x;
		page[x]=0;
	}
	for (int i=1;i<=n;i++)
	{
		if (page[i]==1) c[i]=c[i-1]+1;
		if (page[i]==0) c[i]=0;
	}
	int pos=1000;
	for (int i=n;i>=1;i--)
		if (c[i]>=k)
		{
			pos=i;
			break;
		}
	if (pos==1000)
	{
		cout<<"No solution";
		return 0;
	}
	while (c[pos]>0) pos--;
	cout<<pos+1;
}