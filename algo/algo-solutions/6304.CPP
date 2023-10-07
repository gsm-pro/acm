#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
int n;
vector<int>a,b;
vector<char>used;

bool brute(int j)
{
	while (j<n*2 && b[j]!=-1) ++j;
	if (j==n*2) return true;
	for (int i=0;i<n;++i)
	{
		if (!used[i] && j+a[i]+1<n*2 && b[j+a[i]+1]==-1)
		{
			b[j]=b[j+a[i]+1]=a[i];
			used[i]=true;
			if (brute(j+1)) return true;
			b[j]=b[j+a[i]+1]=-1;
			used[i] = false;
		}
	}
	return false;
}

int main()
{
	cin>>n;
	a.resize(n);
	for (int i=0;i<n;++i) cin>>a[i];
	sort(a.begin(),a.end());
	b.resize(n*2,-1);
	used.resize(n);
	if (brute(0))
		for (int i=0;i<n*2;++i) cout<<b[i]<<" ";
}