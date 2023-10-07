#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n,m;
	cin>>n;
	vector<int> v(n);
	for (int i=0;i<n;i++) cin>>v[i];
	cin>>m;
	vector<double> c(m);
	for (int i=0;i<m;i++) cin>>c[i];
	vector<double> a;
	for (int i=1;i<=m;i++)
		for (int j=0;j<n;j++) a.push_back((i+.0)/v[j]);
	sort(a.begin(),a.end());
	sort(c.begin(),c.end());
	double s=.0;
	for (int i=0;i<m;i++) s+=a[i]*c[m-i-1];
	cout.precision(2);
	cout<<fixed<<s/m;
}