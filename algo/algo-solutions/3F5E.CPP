#include<cstdio>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

int main()
{
	int n;
	scanf("%d",&n);
	vector<pair<int,int>>a(n),z;
	for (int i=0;i<n;i++)
		scanf("%d%d",&a[i].first,&a[i].second);
	sort(a.begin(),a.end());
	z.push_back(a[0]);
	for (int i=1;i<a.size();i++ ) {
		if (a[i].second<z.back().second) z.back()=a[i];else
		if (a[i].first>z.back().second) z.push_back(a[i]);
	}
	printf("%d\n",z.size());
	for (int i=0;i<z.size();i++) printf("%d %d\n",z[i].first,z[i].second);
}