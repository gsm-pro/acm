#include<iostream>
#include<vector>
#define LL long long
using namespace std;
int n,m;
vector<vector<bool>> b,c;
vector<int> color;

void force(int x,int cnt,vector<int> &num)
{
	for (int i=1;i<=n+1;++i)
	{
		if (b[x][i] && num[i]==0)
		{
			num[i]=cnt;
			force(i,cnt,num);
		}
	}
}

int dfs(int x,int ncolor)
{
	int ans=0,t=-1;
	for (int i=2;i<=m;++i)
	{
		if (c[x][i])
		{
			if (color[i]==0)
			{
				color[i]=3-ncolor;
				t=dfs(i,3-ncolor);
				if (t<0) return -1;
				ans+=t;
			} else if (color[i]==ncolor) return -1;
		}
	}
	return ans+1;
}

void print_ans(LL ans)
{
	cout<<ans;
	exit(0);
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>n;
	vector<int> Z(n);
	for (int i=0;i<n;i++) cin>>Z[i];
	b.resize(n+2);
	for (int i=0;i<=n+1;++i) b[i].resize(n+2);
	for (int i=0;i<n;++i)
	{
		for (int j=0;j<Z[i];++j)
		{
			if (j+i+2>n+1) print_ans(0);
			b[j+1][j+i+2]=true;
			b[j+i+2][j+1]=true;
		}
	}
	vector<int> num(n+2,0);
	int cnt=0;
	for (int i=1;i<=n+1;++i)
	{
		if (num[i]==0)
		{
			num[i]=++cnt;
			force(i,cnt,num);
		}
	}
	m=cnt;
	c.resize(m+2);
	for (int i=0;i<=m+1;++i) c[i].resize(m+2);
	for (int i=0;i<n;++i)
	{
		int x=Z[i]+1,y=i+Z[i]+2;
		if (y==n+2) continue;
		if (x<1 || x>n+1 || y<1 || y>n+1) print_ans(0);
		if (num[x]==num[y]) print_ans(0);
		if (num[x]!=1 && num[y]!=1)
		{
			c[num[x]][num[y]]=true;
			c[num[y]][num[x]]=true;
		}
	}
	color.resize(cnt+1,0);
	LL ans=0;
	for (int i=2;i<=m;++i)
	{
		if (color[i]==0)
		{
			color[i]=1;
			if (dfs(i,1)<0) print_ans(0);
			ans++;
		}
	}
	print_ans(3LL<<ans);
}