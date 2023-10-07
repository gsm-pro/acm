#include<iostream>
#include<string>
#include<cmath>
using namespace std;
#define NMAX 1005
#define LMAX 2005
#define KMAX 15
#define INF 1000000000
#define LETTERS_NUM 26
#define OSN 1000000000

enum Type
{
	UP,DOWN,ALT
};

char s[NMAX][LMAX];
int a[KMAX],n,k,c[NMAX][NMAX],prefix[NMAX][NMAX],H[NMAX][LMAX],len[NMAX],d[NMAX],prev[NMAX];
Type type[NMAX][NMAX];
bool u[NMAX];

int min(int q,int w)
{
	if (q<w) return q;
	return w;
}

int dec(int x)
{
	if (x==1) return n;
	return x-1;
}

int calc_prefix(int x,int y)
{
	int l=-1,r=min(len[x],len[y])-1;
	while (l!=r)
	{
		int m=(l+r+1)/2;
		if (H[x][m]==H[y][m]) l=m;else r=m-1;
	}
	return l+1;
}

void write(int y)
{
	int x=prev[y];
	if (!x) return;
	write(x);
	if (type[x][y]==UP)
	{
		for (int i=1;i<=c[x][y];i++) printf("up\n");
	} else
		if (type[x][y]==DOWN)
		{
			for (int i=1;i<=c[x][y];i++) printf("down\n");
		} else {
			printf("Alt\n");
			for (int i=2;i<=c[x][y];i++) printf("%c\n",s[y][i-2]);
		}
}

void solve()
{
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n;j++)
		{
			c[i][j]=min(abs(i-j),n-abs(i-j));
			if (i<j)
			{
				if (c[i][j]==j-i) type[i][j]=DOWN;else type[i][j]=UP;
			} else {
				if (c[i][j]==i-j) type[i][j]=UP;else type[i][j]=DOWN;
			}
		}
	}
	for (int i=1;i<=n;i++)
	{
		H[i][0]=s[i][0]-'a';
		int p=1;
		for (int j=1;s[i][j];j++)
		{
			p=p*LETTERS_NUM;
			if (p>=OSN) p-=OSN;
			H[i][j]=H[i][j-1]+(s[i][j]-'a')*p;
			if (H[i][j]>=OSN) H[i][j]-=OSN;
		}
	}
	for (int i=1;i<=n;i++) len[i]=strlen(s[i]);
	for (int i=1;i<=n-1;i++)
	{
		for (int j=i+1;j<=n;j++)
		{
			prefix[i][j]=calc_prefix(i,j);
			prefix[j][i]=prefix[i][j];
		}
	}
	for (int i=1;i<=n;i++)
	{
		int x=1;
		for (int j=dec(i);j!=i;j=dec(j))
		{
			if (prefix[i][j]+2>x) x=prefix[i][j]+2;
			if (x-1>len[i]) x=INF;
			if (x<c[j][i])
			{
				c[j][i]=x;
				type[j][i]=ALT;
			}
		}
	}
	int res=0;
	a[0]=1;
	for (int t=1;t<=k;t++)
	{
		memset(u,0,sizeof(u));
		memset(prev,0,sizeof(prev));
		for (int i=0;i<=n;i++) d[i]=INF;
		d[a[t-1]]=0;
		while (!u[a[t]])
		{
			int minI=0;
			for (int i=1;i<=n;i++)
				if (!u[i] && (d[i]<d[minI])) minI=i;
			u[minI]=true;
			for (int i=1;i<=n;i++)
			{
				if (d[i]>d[minI]+c[minI][i])
				{
					d[i]=d[minI]+c[minI][i];
					prev[i]=minI;
				}
			}
		}
		printf("%d\n",d[a[t]]);
		write(a[t]);
	}
}

int main()
{
	cin>>n;
	for (int i=1;i<=n;i++) cin>>s[i];
	cin>>k;
	for (int i=1;i<=k;i++) scanf_s("%d",a+i);
	solve();
}