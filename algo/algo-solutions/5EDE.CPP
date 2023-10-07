#include<iostream>
#include<vector>
#include<queue>
using namespace std;
#define forn(i,n) for(int i=0;i<int(n);++i)
#define X first
#define Y second
typedef pair<int,int> pt;
int n,m;
int dx[4]={1, 0, -1,  0};
int dy[4]={0, 1,  0, -1};
int z[101][101];
int dist[101][101][16];
vector<pt> pts;

struct state
{    
	public: 
		int x;
		int y;
		int mk;
};

state curr;

bool checkdoor(int door,int mask)
{
	forn(i,4) if (((mask&(1<<i)))+10==door) return true;
	return false;
}

bool check(int x,int y,int mask)
{
	if (0<=x && x<n && 0<=y && y<m && z[x][y]!=-1)
		if (11<=z[x][y] && z[x][y]<=18) return checkdoor(z[x][y],mask);else return true;
	return false;
}

void main()
{    
	cin>>n>>m;
	memset(z,0,sizeof(z));
	forn(i,n)
		forn(j,m)
		{
			char c;
			cin>>c;
			switch(c)
			{
				case '#':
					z[i][j]=-1;
					break;
				case '*':
					curr.x=i;
					curr.y=j;
					curr.mk=0;
					break;
				case 'b':
					z[i][j]=1;
					break;
				case 'y':
					z[i][j]=2;
					break;
				case 'r':
					z[i][j]=4;
					break;
				case 'g':
					z[i][j]=8;
					break;
				case 'B':
					z[i][j]=11;
					break;
				case 'Y':
					z[i][j]=12;
					break;
				case 'R':
					z[i][j]=14;
					break;
				case 'G':
					z[i][j]=18;
					break;
				case 'X':
					pts.push_back(make_pair(i,j));
					break;
			}
	}
	if (pts.size()==0)
	{
		cout<<-1;
		return;
	}
	memset(dist,63,sizeof(dist));        
	int ans=dist[1][1][1];
	dist[curr.x][curr.y][curr.mk]=0;
	queue<state> q;
	q.push(curr);
	while (!q.empty())
	{
		state v=q.front();
		int mkp=v.mk;
		q.pop();
		if (1<=z[v.x][v.y] && z[v.x][v.y]<=8) v.mk=v.mk | z[v.x][v.y];
		forn(i,4)
		{
			int x1=v.x+dx[i];
			int y1=v.y+dy[i];
			if (check(x1,y1,v.mk))
				if (dist[x1][y1][v.mk]>dist[v.x][v.y][mkp]+1)
				{
					dist[x1][y1][v.mk]=dist[v.x][v.y][mkp]+1;
					state tmp;
					tmp.x=x1;
					tmp.y=y1;
					tmp.mk=v.mk;
					q.push(tmp);
				}
		}
	}
	forn(i,pts.size())
	{
		pt t=pts[i];
		forn(k,16) ans=min(ans,dist[t.X][t.Y][k]);
	}
	if (ans>=9999999) cout<<-1;else cout<<ans;
}