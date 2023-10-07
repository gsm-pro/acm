#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int w[52][52],pred[52][52];
vector<int>a;
int Rec(int l,int r)
{
	if (r==l+1) return 0;
	if (w[l][r]!=-1) return w[l][r];
	int mn=999999,v=0,q=999999;
	for (int i=l+1;i<r;i++) 
	{
		q=min(q,a[r]-a[l]+Rec(l,i)+Rec(i,r));
		if (q<mn) 
		{
			mn=q;
			v=i;
		}
	}
	pred[l][r]=v;
	w[l][r]=q;
	return q;
}

void ans(int l,int r)
{
	if (r==l+1)
		return;
	cout<<a[pred[l][r]]<<" ";
	ans(l,pred[l][r]);
	ans(pred[l][r],r);
}

int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	int n,m,c;
	cin>>m>>n;
	a.push_back(0);
	for (int i=1;i<=n;i++) 
	{
		cin>>c;
		a.push_back(c);
	}
	a.push_back(m);
	sort(a.begin(),a.end());
	for (int i=0;i<52;i++) for (int j=0;j<52;j++) w[i][j]=-1;
	cout<<Rec(0,n+1)<<endl;
	ans(0,n+1);
}