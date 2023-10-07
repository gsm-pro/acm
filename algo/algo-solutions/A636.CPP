#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<string>
using namespace std;
#define forn(i,n) for(int i=0;i<(int)(n);i++)
typedef pair<int,int> pii;

struct st 
{
	int x1,y1,x2,y2,x3,y3,move;
	st(int X1,int Y1,int X2,int Y2,int X3,int Y3,int MOVE)
	{
		x1=X1,y1=Y1,x2=X2,y2=Y2,x3=X3,y3=Y3,move=MOVE;
	}
	st(){}
};

bool operator == (st p1,st p2)
{
	return p1.x1==p2.x1 && p1.y1==p2.y1 && p1.x2==p2.x2 && p1.y2==p2.y2 && 
		p1.x3==p2.x3 && p1.y3==p2.y3 && p1.move==p2.move;
}

bool ans[10][10][10][10][10][10][2],bad[10][10][10][10][10][10][2];
int d[10][10][10][10][10][10][2],deg[10][10][10][10][10][10][2],h,t,n,xx[4],yy[4];
bool u[10][10];
int dx[9]={1,-1, 0, 0, -1,-1, 1, 1, 0};
int dy[9]={0, 0, 1,-1, -1, 1,-1, 1, 0};
st q[1000000],fn;
int ok=0;

void print(int x,int y)
{
	if (ok) swap(x,y);
	printf("%c%d",x+'a',y+1);
}

inline int update(int x)
{
	if (x<0) x+=n;else 
		if (x>=n) x-=n;
	return x;
}

inline void normalize(int &x4,int &y4,int &x5,int &y5,int &x6,int &y6)
{
	if ((x6>y6) || (x6==y6 && min(x4,x5)>min(y4,y5)))
	{
		swap(x4,y4);
		swap(x5,y5);
		swap(x6,y6);
	}
	if (x4>x5 || (x4==x5 && y4>y5))
	{
		swap(x4,x5);
		swap(y4,y5);
	}
}

inline void insert(int x1,int y1,int x2,int y2,int x3,int y3,int move,int tp)
{
	if (tp==-1) bad[x1][y1][x2][y2][x3][y3][move]=1;else
	{
		d[x1][y1][x2][y2][x3][y3][move]=0;
		ans[x1][y1][x2][y2][x3][y3][move]=(tp==1);
		t++;
		q[t]=st(x1,y1,x2,y2,x3,y3,move);
	}	
}

void check(int x1,int y1,int x2,int y2,int x3,int y3,int move)
{
	if (x3>y3 || (x3==y3 && min(x1,x2)>min(y1,y2)) || pii(x1,y1)>=pii(x2,y2) || pii(0,0)==pii(x1,y1) || 
		pii(0,0)==pii(x2,y2) || pii(0,0)==pii(x3,y3) || pii(x1,y1)==pii(x3,y3) || pii(x2,y2)==pii(x3,y3))
	{
		insert(x1,y1,x2,y2,x3,y3,move,-1);
		return;
	}
	forn(i,9)
	{
		int x=update(x3+dx[i]);
		int y=update(y3+dy[i]);
		u[x][y]=0;
	}
	forn(i,8)
		u[(dx[i]+n)%n][(dy[i]+n)%n]=1;
	if (u[x3][y3])
	{
		insert(x1,y1,x2,y2,x3,y3,move,-1);
		return;
	}
	forn(j,2)
	{
		int xt=j ? x1 : x2;
		int yt=j ? y1 : y2;
		forn(i,9)
		{
			int x=update(x3+dx[i]);
			int y=update(y3+dy[i]);
			if ((xt==x || yt==y) && !(xt==x && yt==y)) u[x][y]=1;
		}
	}
	if (u[x3][y3] && !move)
	{
		insert(x1,y1,x2,y2,x3,y3,move,-1);
		return;
	}
	int s=u[x3][y3];
	forn(i,8) s+=(char)u[(x3+dx[i]+n)%n][(y3+dy[i]+n)%n];
	if (s==9 && !move) insert(x1,y1,x2,y2,x3,y3,move,-1);else
		if (s==9 && move) insert(x1,y1,x2,y2,x3,y3,move,0);else
			if (s==8 && !u[x3][y3] && move==1) insert(x1,y1,x2,y2,x3,y3,move,1);else
				forn(i,8)
			{
				int x=update(x3+dx[i]);
				int y=update(y3+dy[i]);
				if (move && !u[x][y] && (pii(x,y)==pii(x1,y1) || pii(x,y)==pii(x2,y2)))
				{
					insert(x1,y1,x2,y2,x3,y3,move,1);
					return;
				}
			}
}

inline void go(int X1,int Y1,int X2,int Y2,int X3,int Y3,int MOVE,int x1,int y1,int x2,int y2,int x3,int y3,int move)
{
	if (bad[x1][y1][x2][y2][x3][y3][move] || d[x1][y1][x2][y2][x3][y3][move]!=-1) return;
	deg[x1][y1][x2][y2][x3][y3][move]--;
	if (!ans[X1][Y1][X2][Y2][X3][Y3][MOVE] || !deg[x1][y1][x2][y2][x3][y3][move])
	{
		d[x1][y1][x2][y2][x3][y3][move]=d[X1][Y1][X2][Y2][X3][Y3][MOVE]+1;
		ans[x1][y1][x2][y2][x3][y3][move]=!ans[X1][Y1][X2][Y2][X3][Y3][MOVE];
		t++;
		q[t]=st(x1,y1,x2,y2,x3,y3,move);
	}
}

void check(int X1,int Y1,int X2,int Y2,int X3,int Y3,int MOVE,int x1,int y1,int x2,int y2,int x3,int y3,int move,int x0,int y0,int px1,int py1,int px2,int py2)
{
	MOVE=1-MOVE;
	move=1-move;
	px2=(px2+n)%n;
	py2=(py2+n)%n;
	if (d[X1][Y1][X2][Y2][X3][Y3][MOVE]==d[x1][y1][x2][y2][x3][y3][move]+1 && ans[X1][Y1][X2][Y2][X3][Y3][MOVE]==!ans[x1][y1][x2][y2][x3][y3][move])
	{
		px1=(px1+x0)%n;
		py1=(py1+y0)%n;
		px2=(px2+x0)%n;
		py2=(py2+y0)%n;
		print(px1,py1);
		printf("-");
		print(px2,py2);
		printf("\n");
		exit(0);
	}
}

inline void find(int x1,int y1,int x2,int y2,int x3,int y3,int move,int tp)
{
	if (move)
	{
		int x4,y4,x5,y5,x6,y6;
		forn(j,2)	
		{
			int xt=j ? x1 : x2;
			int yt=j ? y1 : y2;
			forn(i,4)
			{
				int x=update(xt+dx[i]);
				int y=update(yt+dy[i]);
				while ((x!=x1 || y!=y1) && (x!=x2 || y!=y2))
				{
					if (j)
					{	
						x4=x,y4=y,x5=x2,y5=y2,x6=x3,y6=y3;
					}
					else
					{	
						x4=x1,y4=y1,x5=x,y5=y,x6=x3,y6=y3;
					}
					normalize(x4,y4,x5,y5,x6,y6);
					if (tp==0)
					{
						if (!bad[x4][y4][x5][y5][x6][y6][1-move]) deg[x4][y4][x5][y5][x6][y6][1-move]++;
					} else
						if (tp==1) go(x1,y1,x2,y2,x3,y3,move,x4,y4,x5,y5,x6,y6,1-move);else
							check(x1,y1,x2,y2,x3,y3,move,x4,y4,x5,y5,x6,y6,1-move,xx[0],yy[0],xt,yt,x,y);
					x=update(x+dx[i]);
					y=update(y+dy[i]);
				}
			}
		}
		forn(i,8)
		{
			x4=update(x1+dx[i]);
			y4=update(y1+dy[i]);
			x5=update(x2+dx[i]);
			y5=update(y2+dy[i]);
			x6=update(x3+dx[i]);
			y6=update(y3+dy[i]);
			normalize(x4,y4,x5,y5,x6,y6);
			if (tp==0)
			{
				if (!bad[x4][y4][x5][y5][x6][y6][1-move]) deg[x4][y4][x5][y5][x6][y6][1-move]++;
			} else
				if (tp==1)
					go(x1,y1,x2,y2,x3,y3,move,x4,y4,x5,y5,x6,y6,1-move);
				else	
					check(x1,y1,x2,y2,x3,y3,move,x4,y4,x5,y5,x6,y6,1-move,xx[0],yy[0],0,0,-dx[i],-dy[i]);
		}
	}
	else
	{
		forn(i,8)
		{
			int x6=(x3+dx[i]+n)% n;
			int y6=(y3+dy[i]+n)% n;
			int x4=x1;
			int y4=y1;
			int x5=x2;
			int y5=y2;
			normalize(x4,y4,x5,y5,x6,y6);
			if (tp==0)
			{
				if (!bad[x4][y4][x5][y5][x6][y6][1-move]) deg[x4][y4][x5][y5][x6][y6][1-move]++;
			} else go(x1,y1,x2,y2,x3,y3,move,x4,y4,x5,y5,x6,y6,1-move);
		}	
	}
}

void prepare()
{
	memset(bad,0,sizeof bad);
	memset(d,255,sizeof d);
	h=0;
	t=-1;
	forn(x1,n)
		forn(y1,n)
		forn(x2,n)
		forn(y2,n)
		forn(x3,n)
		forn(y3,n)
		forn(move,2)
		check(x1,y1,x2,y2,x3,y3,move);
	forn(x1,n)
		forn(y1,n)
		forn(x2,n)
		forn(y2,n)
		forn(x3,n)
		forn(y3,n)
		forn(move,2)
		if (!bad[x1][y1][x2][y2][x3][y3][move]) find(x1,y1,x2,y2,x3,y3,move,0);
	while (h<=t)
	{
		st v=q[h];
		if (v==fn) return;
		h++;
		find(v.x1,v.y1,v.x2,v.y2,v.x3,v.y3,v.move,1);
	}
}               

void getData(int &x,int &y)
{
	string s;
	cin>>s;
	char c;
	sscanf(s.data(),"%c%d",&c,&y);
	y--;
	x=c-'a';
}

int main()
{
	scanf("%d",&n);
	forn(i,4) getData(xx[i],yy[i]);
	forn(i,3)
	{
		xx[i+1]=(xx[i+1]-xx[0]+n)%n;
		yy[i+1]=(yy[i+1]-yy[0]+n)%n;
	}
	pii p1,p2,p3;
	int x1,y1,x2,y2,x3,y3,move=0;
	x1=xx[1];
	y1=yy[1];
	x2=xx[2];
	y2=yy[2];
	x3=xx[3];
	y3=yy[3];
	if (x3>y3 || (x3==y3 && min(x1,x2)>min(y1,y2)))
	{
		swap(x1,y1);
		swap(x2,y2);
		swap(x3,y3);
		swap(xx[0],yy[0]);
		ok=1;
	}
	if (pii(x1,y1)>pii(x2,y2))
	{
		swap(x1,x2);
		swap(y1,y2);
	}
	fn=st(x1,y1,x2,y2,x3,y3,move);
	prepare();
	printf("VICTORY\n");
	printf("%d\n",(d[x1][y1][x2][y2][x3][y3][move]+1)/2);
	find(x1,y1,x2,y2,x3,y3,1-move,2);
}