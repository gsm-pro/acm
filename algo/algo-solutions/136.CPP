#include<set>
#include<cstdio>
#include<queue>
#include<deque>
using namespace std;
#define forn(i,n) for(int i=0;i<int(n);i++)
#define forv(i,v) for(int i=0;i!=v.size();i++)
#define N 201
#define E 20001
#define INF 100000001

struct TEdge
{
	int from,to,c,f,p,rev,idx;
};

TEdge e[E];
int next[E];
int e_cnt,n,m,k;
int head[N],d[N],q[N],f[N],from[N];
bool used[N];
deque<int>way;

int add(int from,int to,int c,int p,int idx)
{
	next[e_cnt]=head[from];
	head[from]=e_cnt;
	e[e_cnt].from=from;
	e[e_cnt].to=to;
	e[e_cnt].c=c;
	e[e_cnt].p=p;
	e[e_cnt].f=0;
	e[e_cnt].idx=idx;
	e_cnt++;
	return e_cnt-1;
}

struct Cmp_Heap
{
	bool operator()(const int&p1,const int&p2)const
	{
		return (d[p1]<d[p2]||(d[p1]==d[p2]&&p1<p2));
	}
};

int MinCostFlow(int s,int t,int limit)
{
	memset(used,0,sizeof(used));
	used[s]=true;
	d[s]=0;
	forn (it,n)
	{
		bool ch=true;
		forn (i,n)
			if (used[i])
			{
				int l=head[i];
				while (l!=-1)
				{
					if (e[l].c>0&&d[e[l].to]>d[e[l].from]+e[l].p)
					{
						d[e[l].to]=d[e[l].from]+e[l].p;
						ch=true;
						used[e[l].to]=true;
					}
					l=next[l];
				}
				used[i]=false;
			}
			if (!ch) break;
	}
	forn (i,n) q[i]=d[i];
	int cost=0;
	set<int,Cmp_Heap> h;
	while (limit)
	{
		memset(used,0,sizeof(used));
		memset(d,0,sizeof(d));
		memset(f,0,sizeof(f));
		used[s]=true;
		f[s]=INF;
		h.clear();
		h.insert(s);
		while (h.size())
		{
			int u=*(h.begin());
			h.erase(u);
			int l=head[u];
			while (l!=-1)
			{
				if (e[l].c>e[l].f)
				{
					int newd=d[u]+e[l].p+q[u]-q[e[l].to];
					if (!used[e[l].to]||d[e[l].to]>newd)
					{
						if (used[e[l].to])h.erase(e[l].to);
						d[e[l].to]=newd;
						h.insert(e[l].to);
						used[e[l].to]=true;
						f[e[l].to]=min(f[u],e[l].c-e[l].f);
						from[e[l].to]=l;
					}
				}
				l=next[l];
			}
		}
		if (!used[t]) break;
		cost+=(q[t]+d[t])*f[t];
		int k=t;
		while (k!=s)
		{
			int l=from[k];
			e[l].f+=f[t];
			e[e[l].rev].f-=f[t];
			k=e[l].from;
		}
		forn (i,n)q[i]+=d[i];
		--limit;
	}
	if (limit) return -1;
	return cost;
}

void Bfs(int s,int t)
{
	memset(from,255,sizeof(from));
	memset(used,0,sizeof(used));
	used[s]=true;
	queue<int>q;
	q.push(s);
	while (!q.empty()&&!used[t])
	{
		int u=q.front();
		q.pop();
		int j=head[u];
		while (j!=-1)
		{
			if (e[j].f>0&&!used[e[j].to])
			{
				used[e[j].to]=true;
				q.push(e[j].to);
				from[e[j].to]=j;
			}
			j=next[j];
		}
	}
	way.clear();
	int k=t;
	while (k!=s)
	{
		e[from[k]].f=0;
		way.push_front(e[from[k]].idx);
		k=e[from[k]].from;
	}
}

int main()
{
	memset(head,255,sizeof(head));
	scanf_s("%d%d%d",&n,&m,&k);
	int u,v,w;
	forn (i,m)
	{
		scanf_s("%d%d%d",&u,&v,&w);
		--u;
		--v;
		int p1=add(u,v,1,w,i);
		int p2=add(v,u,0,-w,i);
		e[p1].rev=p2;
		e[p2].rev=p1;
		p1=add(v,u,1,w,i);
		p2=add(u,v,0,-w,i);
		e[p1].rev=p2;
		e[p2].rev=p1;
	}
	int ans=MinCostFlow(0,n-1,k);
	if (ans==-1)
	{
		printf("-1");
		return 0;
	}
	printf("%.5lf\n",ans*1.0/k);
	forn (it,k)
	{
		Bfs(0,n-1);
		printf("%d",int(way.size()));
		forv(i,way) printf(" %d",way[i]+1);
		printf("\n");
	}
}