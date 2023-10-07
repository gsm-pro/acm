#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define LL long long
vector<int> x,way;
int n,k;
bool can[17][17];
LL z[1<<17][17],m;

int gcd(int a,int b)
{
	for (;b;b^=a^=b^=a%=b);
	return a;
}

LL rec(int mask,int last)
{
	if (z[mask][last]!=-1) return z[mask][last];
	if (mask==(1<<n)-1) z[mask][last]=1UL;else
	{
		z[mask][last]=0;
		for (int i=0;i<n;i++)
			if ((mask&(1<<i))==0 && (last==n || can[last][i])) 
				z[mask][last]+=rec(mask|(1<<i),i);
	}
	return z[mask][last];
}

void rec2(int mask,int last,LL rem)
{
	if (mask==(1<<n)-1)
	{
		for (int i=0;i<n;i++) cout<<x[way[i]]<<" ";
		exit(0);
	}
	for (int i=0;i<n;i++)
	{
		if ((mask&(1<<i))==0 && (last==n || can[last][i]))
		{
			if (rem>z[mask^(1<<i)][i])
				rem-=z[mask^(1<<i)][i];
			else
			{
				way.push_back(i);
				rec2(mask^(1<<i),i,rem);
			}
		}
	}
}

int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	cin>>n>>m>>k;
	x.resize(n);
	for (int i=0;i<n;i++) cin>>x[i];
	sort(x.begin(),x.end());
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			if (i!=j && gcd(x[i],x[j])>=k)
				can[i][j]=true;
	memset(z,-1,sizeof z);
	LL kol=rec(0,n);
	if (m>kol)
	{
		cout<<-1;
		return 0;
	}
	rec2(0,n,m);
}