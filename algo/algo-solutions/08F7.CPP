#include<bitset>
#include<string>
#include<iostream>
#include<vector>
using namespace std;
#define K 1501
string s;
int n,ans=0;
vector<bitset<K>> vh(K),ish(K),z(K);
bitset<K> per;

int main()
{
	cin>>n;
	for (int i=0;i<K;i++) z[0].at(i)=1;
	for (int i=1;i<K;i++) 
	{
		z[i]=z[i-1];
		z[i].at(i-1)=0;
	}
	for (int i=0;i<n;i++)
	{
		cin>>s;
		for (int j=0;j<n;j++)
		{
			if (s[j]=='+')
			{
				vh[j].at(i)=1;
				ish[i].at(j)=1;
			}
		}
	}
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			if (i!=j && vh[j].at(i)==1)
			{
				per=(vh[i]&ish[j])&z[max(i,j)];
				ans+=(int)per.count();
			}
	cout<<ans;
}