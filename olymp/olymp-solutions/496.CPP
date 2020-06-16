#include<vector>
#include<algorithm>
#include<cstdio>
using namespace std;
#define INF 1000*1000*1000
vector<pair<pair<int,int>,int>> otr;

bool cmp(pair<pair<int,int>,int> c,pair<pair<int,int>,int> b)
{
	if (c.first.first>b.first.first) return 1;
	if (c.first.first==b.first.first && c.first.second<b.first.second) return 1;
	return 0;
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n;
	scanf_s("%d",&n);
	otr.resize(n);
	for (int i=0;i<n;i++)
	{
		scanf_s("%d%d",&otr[i].first.first,&otr[i].first.second);
		otr[i].second=i;
	}
	sort(otr.begin(),otr.end(),cmp);
	vector<int> a(n);
	for (int i=0;i<n;i++) a[i]=otr[i].first.second;
	vector<int> d (n+1,INF);
	d[0]=-INF;
	vector<int> p(n);
	vector<int> no(n+1);
	no[0]=-1;
	for (int i=0;i<n;i++)
	{
		_w64 int j=upper_bound(d.begin(),d.end(),a[i])-d.begin()-1;
		if (d[j]<=a[i] && a[i]<=d[j+1])
		{
			d[j+1]=a[i];
			p[i]=no[j];
			no[j+1]=i;
		}
	}
	vector<int> result;
	for (int i=n;i>=1;i--)
		if (d[i]!=INF)
		{
			for (int cur=no[i];cur!=-1;cur=p[cur])
				result.push_back(cur);
			break;
		}
	printf("%d\n",(int)result.size());
	for (unsigned i=0;i<result.size();i++) 
		printf("%d %d\n",otr[result[i]].first,otr[result[i]].second);
}