#include<iostream>
#include<queue>
using namespace std;
#define forn(i,n) for(int i=0;i<int(n);++i) 
#define X first
#define Y second
typedef pair<int,int> pt;
int n,m;
int z[22][22];
int cl[22][22];
int dx[8] = {1, 1, 0, -1, -1, -1,  0,  1};
int dy[8] = {0, 1, 1,  1,  0, -1, -1, -1};
const int INF=9999;

bool checks(int x,int y)
{
	if (0<=x && x<n && 0<=y && y<m && z[x][y]!=2) return true;
	return false;
}

int bfs(pt st,pt fin)
{
	memset(cl,63,sizeof(cl));
	if (z[st.X][st.Y]<2)
	{
		cl[st.X][st.Y]=z[st.X][st.Y];
		queue<pt> q;
		q.push(st);
		while(!q.empty())
		{
			pt tpt=q.front();
			q.pop();
			int x=tpt.X;
			int y=tpt.Y;
			forn(i,8)
			{
				int x1=x+dx[i];
				int y1=y+dy[i];
				if (checks(x1,y1))
					if (z[x][y]!=1 || z[x1][y1]!=1)
						if (cl[x][y]+z[x1][y1]<cl[x1][y1])
						{
							cl[x1][y1]=cl[x][y]+z[x1][y1];
							q.push(make_pair(x1,y1));                                
						}
			}
		}
	}
	return cl[fin.X][fin.Y];
}

bool isp(int x,int y)
{        
	if(z[x][y]==2 || z[x][y]>=11) return true;
	return false;
}

int main()
{
	while(cin>>n>>m)
	{
		memset(z,0,sizeof(z));
		pt start,finish;
		cin>>start.X>>start.Y>>finish.X>>finish.Y;
		start.X--;
		start.Y--;
		finish.X--;
		finish.Y--;
		int k;
		cin>>k;
		forn(i,k)
		{
			int a,b;
			char t;            
			cin>>a>>b>>t;
			a--;
			b--;
			int ti;
			switch(t)
			{
				case'u':
					ti=11;
					break;
				case'd':
					ti=12;
					break;
				case'l':
					ti=13;
					break;
				case'r':
					ti=14;
					break;
				case'B':
					ti=2;
					break;
			}
			z[a][b]=ti;
		}
		forn(i,n)
			forn(j,m)
			{
				if(z[i][j]==11)
				{
					z[i][j]=2;
					int x1=i-1;
					while(0<=x1 && !isp(x1,j)) z[x1--][j]=1;
				}
				if(z[i][j]==12)
				{
					z[i][j]=2;
					int x1=i+1;
					while(x1<n && !isp(x1,j)) z[x1++][j]=1;
				}
				if(z[i][j]==13)
				{
					z[i][j]=2;
					int y1=j-1;
					while(y1>=0 && !isp(i,y1)) z[i][y1--]=1;
				}
				if(z[i][j]==14)
				{
					z[i][j]=2;
					int y1=j+1;
					while(y1<m && !isp(i,y1)) z[i][y1++]=1;
				}
			}
		int ans=bfs(start,finish);
		if(ans>INF) cout<<-1<<endl;else cout<<ans<<endl;
	}
}