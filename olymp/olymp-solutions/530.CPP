#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<algorithm>
#include<set>
using namespace std;
#define mp make_pair
#define PII pair<int,int> 
PII z[100001];
set<PII> p,sit,stand;
set<int> stand_numbers;
int n,m,s,prev[100001],aa[100001],bb[100001],d;
long long ans=0;

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d%d%d",&n,&m,&s);
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d%d%d",&aa[i],&bb[i],&prev[i],&d);
		p.insert(mp(prev[i],i));
		p.insert(mp(d,-i));
		z[i]=mp(aa[i]-bb[i],i);
	}
	for (set<PII>::iterator it=p.begin();it!=p.end();it++)
	{
		int time=it->first,action=it->second,number;
		if (action>0) number=action,action=1;
		if (action<0) number=-action,action=-1;
		int a=aa[number],b=bb[number];
		if (action==1)
		{
			if (a<=b)
			{
				stand.insert(mp(a-b,number));
				stand_numbers.insert(number);
			} else {
				if (m>0) 
				{
					sit.insert(mp(a-b,number));
					m--;
				} else
					if (m==0)
					{
						sit.insert(mp(a-b,number));
						PII min=*(sit.begin());
						sit.erase(sit.begin());
						stand.insert(min);
						stand_numbers.insert(min.second);
						if (min.second!=number)
						{
							ans+=(long long)aa[min.second]*(time-prev[min.second]);
							prev[min.second]=time;
						}
					}
			}
		} else {
			if (stand_numbers.count(number)!=0)
			{
				stand_numbers.erase(number);
				stand.erase(z[number]);
				ans+=1LL*b*(time-prev[number]);
			} else {
				sit.erase(z[number]);
				ans+=(long long)a*(time-prev[number]);
				m++;
				if (stand_numbers.size()!=0)
				{
					PII max=*(--stand.end());
					if (max.first>0)
					{
						sit.insert(max);
						m--;
						ans+=(long long)bb[max.second]*(time-prev[max.second]);
						prev[max.second]=time;
						stand.erase(z[max.second]);
						stand_numbers.erase(max.second);
					}
				}
			}
		}
	}
	cout<<ans;
}