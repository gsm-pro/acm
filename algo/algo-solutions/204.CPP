#include<cstdio>
#include<vector>
using namespace std;
typedef vector<vector<int>> graph;
typedef vector<int>::const_iterator const_graph_iter;
vector<int> lca_h,lca_dfs_list,lca_first,lca_tree;
vector<char> lca_dfs_used;

void lca_dfs(const graph &g,int v,int h=1)
{
	lca_dfs_used[v]=true;
	lca_h[v]=h;
	lca_dfs_list.push_back(v);
	for (const_graph_iter i=g[v].begin();i!=g[v].end();++i)
		if (!lca_dfs_used[*i])
		{
			lca_dfs(g,*i,h+1);
			lca_dfs_list.push_back(v);
		}
}

void lca_build_tree(int i,int l,int r)
{
	if (l==r)
		lca_tree[i]=lca_dfs_list[l];
	else
	{
		int m=(l+r)>>1;
		lca_build_tree(i+i,l,m);
		lca_build_tree(i+i+1,m+1,r);
		if (lca_h[lca_tree[i+i]]<lca_h[lca_tree[i+i+1]])
			lca_tree[i]=lca_tree[i+i];
		else
			lca_tree[i]=lca_tree[i+i+1];
	}
}

void lca_prepare(const graph &g,int root)
{
	int n=(int)g.size();
	lca_h.resize(n);
	lca_dfs_list.reserve(n*2);
	lca_dfs_used.assign(n,0);
	lca_dfs(g,root);
	int m=(int)lca_dfs_list.size();
	lca_tree.assign(lca_dfs_list.size()*4+1,-1);
	lca_build_tree(1,0,m-1);
	lca_first.assign(n,-1);
	for (int i=0;i<m;++i)
	{
		int v=lca_dfs_list[i];
		if (lca_first[v]==-1) lca_first[v]=i;
	}
}

int lca_tree_min(int i,int sl,int sr,int l,int r)
{
	if (sl==l && sr==r) return lca_tree[i];
	int sm=(sl+sr)>>1;
	if (r<=sm) return lca_tree_min(i+i,sl,sm,l,r);
	if (l>sm) return lca_tree_min(i+i+1,sm+1,sr,l,r);
	int ans1=lca_tree_min(i+i,sl,sm,l,sm);
	int ans2=lca_tree_min(i+i+1,sm+1,sr,sm+1,r);
	return lca_h[ans1]<lca_h[ans2] ? ans1:ans2;
}

int lca(int a,int b)
{
	int left=lca_first[a],right=lca_first[b];
	if (left>right) swap(left,right);
	return lca_tree_min(1,0,(int)lca_dfs_list.size()-1,left,right);
}

int mod(int a,int b)
{
	if (a%b==0) return b;
	return (a%b);
}

int main()
{
	int n,l;
	graph g;
	scanf_s("%d",&n);
	g.resize(n);
	int v1,v2;
	for(int i=1;i<=n-1;i++)
	{
		scanf_s("%d%d",&v1,&v2);
		v1--;
		v2--;
		g[v1].push_back(v2);
		g[v2].push_back(v1);
	}
	int root=mod(8191*n+511,n)-1;
	lca_prepare(g,root);
	v1=1;
	v2=n;
	for (int i=1;i<=n;i++)
	{
		if (i>1)
		{
			v1=mod(2*v1+3*v2,n);
			v2=mod(l*1009+17,n);
		}
		v1--;
		v2--;
		l=lca(v1,v2)+1;
		printf("%d ",l);
		v1++;
		v2++;
	}
}