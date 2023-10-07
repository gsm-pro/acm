#include<iostream>
#include<string>
using namespace std;
#define C(z) (int)z.size()
#define LL long long
string s,res;
LL k,d[51][26],d0[51][26],m[51][60],cur[26],cur0[26],sum=0;

int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	cin>>s>>k;
	for (int i=C(s)-1;i>=0;i--)
	{
		for (int alph=0;alph<26;alph++)
		{
			d[i][alph]=d[i+1][alph];
			d0[i][alph]=d0[i+1][alph];
		}
		d0[i][s[i]-'A']++;
		d[i][s[i]-'A']+=(sum+1);
		sum=2*sum+1;
	}
	if (k==1) return 0;
	--k;
	for (int alph=0;alph<26;alph++)
	{
		cur[alph]=d[0][alph];
		cur0[alph]=d0[0][alph];
	}
	while (true)
	{
		int next_char;
		for (int alph=0;alph<26;alph++)
		{
			if (cur[alph]>=k)
			{
				next_char=alph;
				break;
			} else k-=cur[alph];
		}
		res+=(next_char+'A');
		if (k<=cur0[next_char]) break;
		k-=cur0[next_char];
		memset(m,0,sizeof m);
		m[0][0]=1;
		for (int i=0;i<C(s);i++)
			for (int j=0;j<C(res);j++)
				for (int k=i;k<C(s);k++)
					if (s[k]==res[j])
						m[k+1][j+1]+=m[i][j];
		memset(cur,0,sizeof cur);
		memset(cur0,0,sizeof cur0);
		for (int i=1;i<=C(s);i++)
		{
			for (int alph=0;alph<26;alph++)
			{
				cur[alph]+=d[i][alph]*m[i][res.size()];
				cur0[alph]+=d0[i][alph]*m[i][res.size()];
			}
		}
	}
	cout<<res;
}