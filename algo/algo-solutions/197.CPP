#include<iostream>
#include<string>
using namespace std;
#define forn(i,n) for(int i=0;i<(int)(n);i++)

struct rec
{
	int xc,yc,xt,yt,mv;
	rec(int x1,int y1,int x2,int y2,int _mv)
	{
		xc=x1;
		yc=y1;
		xt=x2;
		yt=y2;
		mv=_mv;
	}
	rec(){}
};

int n,m,ans[10][10][10][10][2],d[10][10][10][10][2];
char a[20][20];
int dx[9]={0,-1, 1, 0, 0, -1,-1, 1, 1};
int dy[9]={0, 0, 0,-1, 1, -1, 1,-1, 1};
int h,t;
rec q[50000];

bool ok(int x1,int y1)
{
	if (!(0<=x1 && x1<n && 0<=y1 && y1<m)) return false;
	return a[x1][y1]!='*';
}

void calc(int xc,int yc,int xt,int yt,int mv)
{
	if (!ok(xc,yc) || !ok(xt,yt))
	{
		ans[xc][yc][xt][yt][mv]=-3;
		return;
	}
	if (xc==xt && yc==yt)
	{
		ans[xc][yc][xt][yt][mv]=1-mv;
		t++;
		q[t]=rec(xc,yc,xt,yt,mv);
		return;
	}
	if (a[xt][yt]=='E')
	{
		ans[xc][yc][xt][yt][mv]=mv;
		t++;
		q[t]=rec(xc,yc,xt,yt,mv);
		return;
	}
	d[xc][yc][xt][yt][mv]=0;
	forn(i,9)
		if ((i<5 || !mv) && ok(xc+(1-mv)* dx[i],yc+(1-mv)*dy[i]) && ok(xt+mv*dx[i],yt+mv*dy[i])) d[xc][yc][xt][yt][mv]++;
}

void main ()
{
	cin>>n>>m;
	string r;
	forn(i,n)
	{
		cin>>r;
		forn(j,r.length()) a[i][j]=r[j];
	}
	memset(ans,255,sizeof(ans));
	memset(d,0,sizeof(d));
	h=0;
	t=-1;
	forn(x1,n)
		forn(y1,m)
			forn(x2,n)
				forn(y2,m)
					forn(i,2)
						calc(x1,y1,x2,y2,i);
	while (h<=t)
	{
		rec v=q[h];
		h++;
		rec w;
		forn(i,9)
			if (i<5 || v.mv)
			{
				w.xc=v.xc+dx[i]*v.mv;
				w.yc=v.yc+dy[i]*v.mv;
				w.xt=v.xt+dx[i]*(1-v.mv);
				w.yt=v.yt+dy[i]*(1-v.mv);
				w.mv=1-v.mv;
				if (!ok(w.xc,w.yc) || !ok(w.xt,w.yt)) continue;
				if (ans[w.xc][w.yc][w.xt][w.yt][w.mv]!=-1) continue;
				int s=ans[v.xc][v.yc][v.xt][v.yt][v.mv];
				if (s==0)
				{
					ans[w.xc][w.yc][w.xt][w.yt][w.mv]=1;
					t++;
					q[t]=w;
				}
				else
				{
					d[w.xc][w.yc][w.xt][w.yt][w.mv]--;
					if (!d[w.xc][w.yc][w.xt][w.yt][w.mv])
					{
						ans[w.xc][w.yc][w.xt][w.yt][w.mv]=0;
						t++;
						q[t]=w;
					}
				}
			}
	}
	int xc,yc,xt,yt,mv;
	xc=yc=xt=yt=-1;
	forn(i,n)
		forn(j,m)
			if (a[i][j]=='C')
			{
				xc=i;
				yc=j;
			}
			else
				if (a[i][j]=='T')
				{
					xt=i;
					yt=j;
				}
	mv=0;
	if (ans[xc][yc][xt][yt][mv]==1)
	{
		cout<<"WIN";
		return;
	}
	if (ans[xc][yc][xt][yt][mv]==0)
	{
		cout<<"LOSS";
		return;
	}
	cout<<"DRAW";
}