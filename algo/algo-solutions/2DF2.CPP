#include<cstdio>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

int main()
{
	int n;
	scanf("%d",&n);
	vector<pair<int,int>>a(n);
	vector<int>z;
	for (int i=0;i<n;i++)
		scanf("%d%d",&a[i].first,&a[i].second);
	sort(a.begin(),a.end());
	z.push_back(a[0].second);
	for (int i=1;i<a.size();i++ ) {
		if (a[i].second<z.back()) z.back()=a[i].second;else
			if (a[i].first>z.back()) z.push_back(a[i].second);else z.back()=max(z.back(),a[i].first);
	}
	printf("%d\n",z.size());
	for (int i=0;i<z.size();i++) printf("%d ",z[i]);
}