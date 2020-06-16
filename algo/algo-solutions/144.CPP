#include<iostream>
#include<vector>
using namespace std;
#define LL __int64

int main()
{
	LL F[20]={1};
	for (int i=1;i<=19;i++) F[i]=F[i-1]*i;
	int n,k;
	cin>>n>>k;
	k--;
	vector<int> p(n,0);
	for (int i=0;i<n;i++)
	{
		p[i]=int(k/F[n-i-1])+1;
		k%=F[n-i-1];
	}
	for (int i=n-2;i>=0;i--)
		for (int j=i+1;j<n;j++) if (p[j]>=p[i]) p[j]++;
	copy(p.begin(),p.end(),ostream_iterator<int>(cout," "));
}