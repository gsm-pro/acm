#include<iostream>
using namespace std;

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int a[25],n,s,q,k=0;
	cin>>n>>s;
	for (int i=0;i<n;i++) cin>>a[i];
	for (int m=1;m<=((1<<n)-1);m++)
	{
		q=0;
		for (int i=0;i<n;i++) if ((m>>i)&1) q+=a[i];
		if (q==s)
		{
			cout<<"Yes"<<endl;
			for (int i=0;i<n;i++) if ((m>>i)&1) k++;
			cout<<k<<endl;
			for (int i=0;i<n;i++) if ((m>>i)&1) cout<<a[i]<<" ";
			return 0;
		}
	}
	cout<<"No";
}