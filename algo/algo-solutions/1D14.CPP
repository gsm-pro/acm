#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
using namespace std;
const int inf=1000000000;

int main()
{
	int n,m;
	scanf_s("%d%d",&n,&m);
	vector<int> p(n);
	for (int i=0;i<n;i++) scanf_s("%d",&p[i]);
	bool ok=true;
	vector<int> cost(m),new_cost(m),dec(n,inf),dec_id(n,-1);
	dec[0]=0;
	for (int i=0;i<m;++i) 
	{
		int a,b,c;
		scanf_s("%d%d%d",&a,&b,&c);
		a--;
		b--;
		cost[i]=c;
		for (int j=0;j<=1;++j) 
		{
			int razn=p[b]-p[a]-c;
			if (razn>0) 
			{
				ok&=(new_cost[i]==0 || new_cost[i]==razn);
				new_cost[i]=razn;
				dec[b]=0;
			} else
			if (-razn<=c && -razn<dec[b]) 
			{
				dec[b]=-razn;
				dec_id[b]=i;
			}
			swap(a,b);
		}
	}
	for (int i=0;i<n;++i)
	{
		ok&=(dec[i]!=inf);
		int r_id=dec_id[i];
		if (r_id!=-1) 
		{
			ok&=(new_cost[r_id]==0 || new_cost[r_id]==-dec[i]);
			new_cost[r_id]=-dec[i];
		}
	}
	if (!ok) printf("-1");else 
	{
		long long sum=0;
		for (int i=0;i<m;++i) sum+=abs(new_cost[i]);
		cout<<sum<<endl;
		for (int i=0;i<m;++i) printf("%d\n",cost[i]+new_cost[i]);
	}
}