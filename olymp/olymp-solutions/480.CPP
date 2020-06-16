#include<iostream>
#include<cmath>
using namespace std;
#define MAX 1000001
int primes[MAX],cnt=-1;
bool isPrime[MAX];
long long ans=0;

struct
{
	int first;
	int second;
} divs[255];

int fmd(int &n)
{
	if (isPrime[n]) return n;
	for (int i=0;i<=cnt;i++)
		if (n%primes[i]==0) 
			return primes[i];
	return 1;
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n,m;
	cin>>n>>m;
	n--,m--;
	if (n>m) swap(n,m);
	memset(isPrime,true,sizeof isPrime);
	for (int i=2;i*i<=MAX;i++)
		if (isPrime[i])
			for (int j=i*i;j<=MAX;j+=i)
				isPrime[j]=false;
	for (int i=2;i<MAX;i++)
		if (isPrime[i])
			primes[++cnt]=i;
	for (int z=1;z<=n;z++)
	{
		int cur=0,number=z,last_prime=0;
		while (number>1)
		{
			int prime=fmd(number);
			if (prime!=last_prime)
			{
				int size=cur;
				for (int i=0;i<size;i++)
				{
					divs[cur].first=prime*divs[i].first;
					divs[cur].second=divs[i].second+1;
					cur++;
				}
				divs[cur].first=prime,divs[cur].second=1,cur++;
				last_prime=prime;
			}
			number/=prime;
		}
		int gcd_greater_1=0;
		for (int i=0;i<cur;i++)
		{
			int d=m/divs[i].first;
			if (divs[i].second&1) gcd_greater_1+=d;else gcd_greater_1-=d;
		}
		int gcd_1=m-gcd_greater_1;
		ans+=gcd_1*1LL;
	}
	if (n==0 && m==0) cout<<0;else
		if (n==0 || m==0) cout<<1;else 
			cout<<ans+2LL;
}