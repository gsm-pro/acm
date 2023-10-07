#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<bitset>
#include<vector>
#include<algorithm>
#define has(m,i) (int)((((m)>>(i))&1)!=0)
#define INF 1<<30
#define LEN 150
using namespace std;
#define bset vector<bitset<LEN>>
int n,m,t,k,Q,ans=INF;
pair<int,int> msk[265000],zh[19];
bset flies,can[19];

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	Q=n/LEN+1;
	for (int i=0;i<m;i++)
		scanf("%d%d",&zh[i].second,&zh[i].first);
	flies.resize(Q);
	for (int i=0;i<k;i++)
	{
		scanf("%d",&t);
		int p=t/LEN;
		t-=p*LEN;
		flies[p].set(t);
	}
	for (int i=0;i<m;i++)
	{
		can[i].resize(Q);
		for (int j=zh[i].second;j<=n;j+=zh[i].second)
		{
			int p=j/LEN,jj=j;
			jj-=p*LEN;
			can[i][p].set(jj);
		}
	}
	for (int i=0;i<Q;i++) flies[i]=~flies[i];
	for (int z=0;z<(1<<m);z++)
	{
		int sum=0;
		for (int i=0;i<m;i++)
			if (has(z,i)) sum+=zh[i].first;
		msk[z]=make_pair(sum,z);
	}
	sort(msk,msk+(1<<m));
	for (int w=0;w<(1<<m);w++)
	{
		int sum=msk[w].first,z=msk[w].second;
		if (sum>=ans) break;
		for (int p=0;p<m;p++)
		{
			if (has(z,p)) continue;
			bool ok=true;
			for (int j=0;j<Q && ok;j++)
			{
				bitset<LEN> all,closed;
				for (int i=0;i<m;i++)
					if (has(z,i)) all|=can[i][j];
				closed=flies[j]|all;
				if ((closed&can[p][j])!=can[p][j]) ok=false;
			}
			if (ok) ans=min(ans,sum+zh[p].first);
		}
	}
	if (ans!=INF) cout<<ans;else cout<<-1;
}