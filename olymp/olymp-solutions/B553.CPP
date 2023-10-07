#include<iostream>
#include<cmath>
using namespace std;
#define MAX 2000001
int prmul[MAX],primes[MAX];
bool isPrime[MAX],was[MAX];
int last=2,count=-1;

int fmd(int n)
{
	if (isPrime[n]) return n;
	for (int i=0;i<count;i++)
		if (n%primes[i]==0) 
			return primes[i];
	return 1;
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n;
	cin>>n;
	if (n==1)
	{
		cout<<1;
		return 0;
	}
	memset(isPrime,true,sizeof isPrime);
	for (int i=2;i*i<=MAX;i++)
		if (isPrime[i])
			for (int j=i*i;j<=MAX;j+=i)
				isPrime[j]=false;
	for (int i=2;i<MAX;i++)
	{
		if (isPrime[i])
		{
			prmul[i]=1;
			primes[++count]=i;
		}
	}
	prmul[2]=2;
	for (int i=2;i<=n-1;i++)
	{
		int number=last,minvalue=1<<30;
		int last_prime=0;
		while (number>1)
		{
			int prime=fmd(number);
			if (prime!=last_prime) 
			{
				while (was[prmul[prime]*prime]) prmul[prime]++;
				minvalue=min(minvalue,prmul[prime]*prime);
			}
			number/=prime;
			last_prime=prime;
		}
		was[minvalue]=true;
		last=minvalue;
	}
	cout<<last;
}