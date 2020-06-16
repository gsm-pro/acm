#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

int main()
{
	int n;
	cin>>n;
	vector<vector<double>> a(n,vector<double>(n+1));
	for (int i=0;i<n;i++)
		for (int j=0;j<=n;j++) cin>>a[i][j];
	for (int i=0;i<n;++i)
	{
		int k=i;
		for (int j=i+1;j<n;++j)
			if (fabs(a[j][i])>fabs(a[k][i])) k=j;
		swap(a[i],a[k]);
		for (int j=i+1;j<=n;++j) a[i][j]/=a[i][i];
		for (int j=0;j<n;++j)
			if (j!=i)
				for (int k=i+1;k<=n;++k) a[j][k]-=a[i][k]*a[j][i];
	}
	cout.setf(ios::fixed);
	cout.precision(20);
	for (int i=0;i<n;++i) cout<<fixed<<a[i][n]<<" ";
}