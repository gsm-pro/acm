#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef vector<int> VInt;
typedef vector<VInt> VVInt;
typedef VInt::iterator VIter;
typedef pair<int,int> PInt;
typedef vector<PInt> VPInt;
typedef vector<VPInt> VVPInt;
typedef VPInt::iterator VPIter;
VVInt graph;
VInt colors,parents,enter,leave,low,bcc;
int myTime=0,newIndex=0;

void visitLow(int u)
{
	colors[u]=1;
	low[u]=enter[u]=++myTime;
	for (VIter it=graph[u].begin();it!=graph[u].end();it++)
	{
		if (colors[*it]==0)
		{
			parents[*it]=u;
			visitLow(*it);
			low[u]=min(low[u],low[*it]);
		} else if (colors[*it]==1 && *it!=parents[u])
		{
			low[u]=min(low[u],enter[*it]);
		}
	}
	colors[u]=2;
	leave[u]=++myTime;      
}

void visitBCC(int u)
{
	for (VIter it=graph[u].begin();it!=graph[u].end();it++)
	{
		if(parents[*it]==u)
		{
			bcc[*it]=(low[*it]<enter[u]) ? bcc[u] : (low[*it]>enter[u]) ? -1 : (newIndex++);     
			visitBCC(*it);         
		}
	}
}

int getBCC(int u,int v)
{
	return bcc[(enter[u]>enter[v]) ? u : v];
}

int main()
{
	int n,m;
	scanf_s("%d%d",&n,&m);
	graph.resize(n);
	while (m--)
	{
		int from,to;
		scanf_s("%d%d",&from,&to);
		graph[from-1].push_back(to-1);
		graph[to-1].push_back(from-1);
	}
	colors.assign(n,0);
	parents.assign(n,-1);
	enter.resize(n);
	leave.resize(n);
	low.resize(n);
	for (int i=0;i<n;i++)
		if(colors[i]==0) visitLow(i);
	bcc.assign(n,-1);
	for (int i=0;i<n;i++)
		if(parents[i]==-1) visitBCC(i);   
	VPInt bridges;
	VVPInt comps(newIndex);
	for (int i=0;i<n;i++)
	{
		for (VIter it=graph[i].begin();it!=graph[i].end();it++)
		{
			if (i<*it)
			{
				int id=getBCC(i,*it);
				((id==-1) ? bridges : comps[id]).push_back(PInt(i,*it));
			}
		}
	}
	printf("%d\n",bridges.size()+newIndex);
	for (VPIter bridge=bridges.begin();bridge!=bridges.end();bridge++)
		printf("1\n%d %d\n",bridge->first+1,bridge->second+1);
	for (int i=0;i<newIndex;i++)
	{
		printf("%d\n",comps[i].size());
		for (VPIter edge=comps[i].begin();edge!=comps[i].end();edge++)
			printf("%d %d\n",edge->first+1,edge->second+1);      
	}
}