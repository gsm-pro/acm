#include<iostream>
#include<string>
#include<vector>
#include<queue>
using namespace std;
#define forn(i,n) for(int i=0;i<n;i++)
#define PII pair<int,int>
#define mp make_pair
#define x first
#define y second

struct pos
{
	PII k,l1,l2;
	int dst;
	char win,move;
	pos(){}
	pos(PII kp,PII l1p,PII l2p,int _move)
	{
		k=kp,l1=l1p,l2=l2p,move=_move;
	}
	bool operator == (pos a)
	{
		return (this->k==a.k && this->l1==a.l1 && 
			this->l2==a.l2 && this->move==a.move);
	}
};

queue<pos> q;
PII l1,l2,kw,kb;
int d[10][10][10][10][10][10][2],
    h[10][10][10][10][10][10][2],
    dst[10][10][10][10][10][10][2];
pos tmp[10*10];
int chtmp[10*10],ktmp=0,n;
bool exist;
int dkx[8]={-1,-1,0,1,1,1,0,-1};
int dky[8]={0,1,1,1,0,-1,-1,-1};
int dlx[4]={-1,0,1,0};
int dly[4]={0,1,0,-1};

PII operator + (PII a,PII b)
{
	return mp((a.x+b.x+n)%n,(a.y+b.y+n)%n);
}

PII operator - (PII a,PII b)
{
	return mp((a.x-b.x+n)%n,(a.y-b.y+n)%n);
}

void operator += (PII &a,PII b)
{
	a=a+b;
}

void operator -= (PII &a,PII b)
{
	a=a-b;
}

int dist1(int a,int b)
{
	int res=abs(a-b);
	return min(res,n-res);
}

int dist(PII k1,PII k2)
{
	return max(dist1(k1.x,k2.x),dist1(k1.y,k2.y));
}

bool fight(PII l,PII k)
{
	return (l.x==k.x)^(l.y==k.y);
}

int correct_pos(pos &c)
{
	int res;
	if (dist(mp(0,0),c.k)<=1) return (res=0);
	if (c.k==c.l1 || c.k==c.l2 || c.l1==c.l2) return (res=0);
	if (c.k==mp(0,0) || mp(0,0)==c.l1 || c.l2==mp(0,0)) return (res=0);
	if (c.move==1)
	{
		if (fight(c.l1,c.l2)) return (res=1);
		if (dist(c.l1,c.k)<=1 && dist(c.l1,mp(0,0))>1) return (res=0);
		if (dist(c.l2,c.k)<=1 && dist(c.l2,mp(0,0))>1) return (res=0);
	} 
	else 
	{
		if (fight(c.l1,c.k) || fight(c.l2,c.k)) return (res=0);
	}
	return (res=1);		
}

void push(pos &u,bool put,int ch)
{
	exist=true;
	if (put)
	{
		chtmp[ktmp]=ch;
		tmp[ktmp++]=u;
	}
}

void push2(pos &u)
{
	tmp[ktmp++]=u;
}

void go(pos &c,bool put=false)
{
	ktmp=0;
	exist=false;
	int st=0;
	if (c.move==1)
	{
		forn(i,8)
		{
			pos cn=c;
			cn.move=1-c.move;
			cn.k=c.k+mp(dkx[i],dky[i]);
			if (correct_pos(cn))
			{
				++st;
				push(cn,put,0);
			}
		}
	} 
	else 
	{
		forn(i,8)
		{
			pos cn=c;
			cn.move=1-c.move;
			cn.k=c.k-mp(dkx[i],dky[i]);
			cn.l1=c.l1-mp(dkx[i],dky[i]);
			cn.l2=c.l2-mp(dkx[i],dky[i]);
			if (correct_pos(cn))
			{
				++st;
				push(cn,put,0);
			}
		}
		int km[4]; 
		memset(km,0,sizeof(km));
		forn(d,4)
		{
			pos cn=c;
			cn.move=1-c.move;
			int ug=n-km[(d+2)&3];
			forn(i,ug)
			{
				cn.l1=cn.l1+mp(dlx[d],dly[d]);
				if (correct_pos(cn))
				{
					++st;
					if (put) push(cn,put,1);
				}
				if (cn.l1==cn.l2 || cn.l1==mp(0,0)) break;
				++km[d];
			}
		}
		memset(km,0,sizeof(km));
		forn(d,4)
		{
			pos cn=c;
			cn.move=1-c.move;
			int ug=n-km[(d+2)&3];
			forn(i,ug)
			{
				cn.l2=cn.l2+mp(dlx[d],dly[d]);
				if (correct_pos(cn))
				{
					++st;
					push(cn,put,2);
				}
				if (cn.l1==cn.l2 || cn.l2==mp(0,0)) break;
				++km[d];
			}
		}
	}
	d[c.l1.x][c.l1.y][c.l2.x][c.l2.y][c.k.x][c.k.y][c.move] = st;
}

void go2(pos &c,bool put=true)
{
	ktmp=0;
	exist=false;
	int st=0;
	c.move=1-c.move;
	if (c.move==1)
	{
		forn(i,8)
		{
			pos cn=c;
			cn.k=c.k+mp(dkx[i],dky[i]);
			if (correct_pos(cn))
			{
				++st;
				if (put) push2(cn);
			}
		}
	} 
	else 
	{
		forn(i,8)
		{
			pos cn=c;
			cn.k=c.k-mp(dkx[i],dky[i]);
			cn.l1=c.l1-mp(dkx[i],dky[i]);
			cn.l2=c.l2-mp(dkx[i],dky[i]);
			if (correct_pos(cn))
			{
				++st;
				if (put) push2(cn);
			}
		}
		int km[4]; 
		memset(km,0,sizeof(km));
		forn(d,4)
		{
			pos cn=c;
			int ug=n-km[(d+2)&3];
			forn(i,ug)
			{
				cn.l1=cn.l1+mp(dlx[d],dly[d]);
				if (correct_pos(cn))
				{
					++st;
					if (put) push2(cn);
				}
				if (cn.l1==cn.l2 || cn.l1==mp(0,0)) break;
				++km[d];
			}
		}
		memset(km,0,sizeof(km));
		forn(d,4)
		{
			pos cn=c;
			int ug=n-km[(d+2)&3];
			forn(i,ug)
			{
				cn.l2=cn.l2+mp(dlx[d],dly[d]);
				if (correct_pos(cn))
				{
					++st;
					if (put) push2(cn);
				}
				if (cn.l1==cn.l2 || cn.l2==mp(0,0)) break;
				++km[d];
			}
		}
	}
}

void put_h(pos &c,int r,int pdst)
{
	c.dst=pdst+1;
	int &t=h[c.l1.x][c.l1.y][c.l2.x][c.l2.y][c.k.x][c.k.y][c.move];
	c.win=r;
	if (t==-1)
	{
		dst[c.l1.x][c.l1.y][c.l2.x][c.l2.y][c.k.x][c.k.y][c.move]=pdst+1;
		q.push(c);
	}
	t=r;
}

void dec_d(pos &c,int pdst)
{
	int &t=d[c.l1.x][c.l1.y][c.l2.x][c.l2.y][c.k.x][c.k.y][c.move];
	t--;
	if (t==0) put_h(c,0,pdst);
}

void make()
{
	memset(h,255,sizeof(h));
	memset(d,0,sizeof(d));
	memset(dst,255,sizeof(dst));
	forn(xl1,n)
		forn(yl1,n)
			forn(xl2,n)
				forn(yl2,n)
					forn(xkb,n)
						forn(ykb,n)
							forn(move,2)
							{
								pos c=pos(mp(xkb,ykb),mp(xl1,yl1),mp(xl2,yl2),move);
								if (!correct_pos(c)) continue;
								go(c,false);
								if (c.move==1)
								{
									if ((fight(c.l1,c.k) || fight(c.l2,c.k)) && !exist)
									{
										put_h(c,0,-1);
										c.win=false;
									}
									if ((!fight(c.l1,c.k) && !fight(c.l2,c.k)) && !exist)
									{
										put_h(c,2,-1);
										c.win=false;
									}
								}
							}
}

void process()
{
	make();
	while (!q.empty())
	{
		pos c=q.front();
		q.pop();
		go2(c);
		if (c.win==1)
			forn(i,ktmp)
				dec_d(tmp[i],c.dst);
		if (c.win==0)
			forn(i,ktmp)
				put_h(tmp[i],1,c.dst);
	}
}

PII getPoint(string s)
{
	PII res;
	res.x=s[0]-'a',res.y=0;
	for (int i=1;i<(int)s.length();i++) res.y=res.y*10+s[i]-'0';
	res.y--;
	return res;
}

void input()
{
	string sl1,sl2,skw,skb;
	cin>>n>>skw>>sl1>>sl2>>skb;
	l1=getPoint(sl1),l2=getPoint(sl2),kw=getPoint(skw),kb=getPoint(skb);
}

void output()
{
	pos start;
	start.k=kb-kw,start.l1=l1-kw,start.l2=l2-kw,start.move=0;
	pos cur=start;
	if (h[cur.l1.x][cur.l1.y][cur.l2.x][cur.l2.y][cur.k.x][cur.k.y][cur.move]==0)
	{
		cout<<"DRAW";
		return;
	}
	int r=dst[cur.l1.x][cur.l1.y][cur.l2.x][cur.l2.y][cur.k.x][cur.k.y][cur.move];
	cout<<"VICTORY"<<endl<<(r+1)/2<<endl;
	go(start,true);
	forn(i,ktmp)
	{
		pos cur=tmp[i];
		PII p1,p2;
		if (h[cur.l1.x][cur.l1.y][cur.l2.x][cur.l2.y][cur.k.x][cur.k.y][cur.move]==1) continue;
		if (dst[cur.l1.x][cur.l1.y][cur.l2.x][cur.l2.y][cur.k.x][cur.k.y][cur.move]!=r-1) continue;
		cur=tmp[i];
		int chgs=(int)(start.l1!=cur.l1)+(int)(start.l2!=cur.l2)+(int)(start.k!=cur.k);
		if (chgs<=1)
		{
			if (chgs==1)
			{
				if (start.l1!=cur.l1) p1=start.l1,p2=cur.l1;else p1=start.l2,p2=cur.l2;
			} 
			else 
			{
				if (chtmp[i]==1) p1=p2=start.l1;else p1=p2=start.l2;
			}
		}
		else p1=mp(0,0),p2=start.l2-tmp[i].l2;
		p1+=kw,p2+=kw;
		cout<<(char)('a'+p1.x)<<p1.y+1<<"-"<<(char)('a'+p2.x)<<p2.y+1<<endl;
		break;
	}
}

int main()
{
	input();
	process();
	output();
}