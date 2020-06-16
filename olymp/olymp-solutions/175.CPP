#include<algorithm>
#include<cstdio>
#include<queue>
#include<vector>
using namespace std;

int main() 
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n,k,a,b,ans=0;
	scanf_s("%d%d",&n,&k);
	vector<int> d;
	vector<pair<int,int>> w;
	for (int i=0;i<n;i++)
	{
		scanf_s("%d%d",&a,&b);
		w.push_back(make_pair(a,b));
	}
	for (int i=0;i<k;i++)
	{
		scanf_s("%d",&a);
		d.push_back(a);
	}
	sort(d.begin(),d.end());
	sort(w.begin(),w.end());
	unsigned j=0;
	priority_queue<int> q;
	for (unsigned i=0;i<d.size();i++) 
	{
		while (j<w.size() && w[j].first<=d[i]) q.push(w[j++].second);
		if (q.size()) ans+=q.top(),q.pop();
	}
	printf("%d",ans);
}