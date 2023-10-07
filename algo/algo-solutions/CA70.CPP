#include<iostream>
using namespace std;
const int INF=1000000000;
#define F(i,n) for(int i=0;i<(n);i++)

int main() 
{
	int n,d[101][101];
	cin>>n;
	F(i,n) F(j,n) {
		cin>>d[i][j];
		if (i!=j && d[i][j]==0)
			d[i][j]=INF;
		if (i==j && d[i][j]>0)
			d[i][j]=0;
	}
	F(k,n) F(i,n) F(j,n) {
		if (d[i][k]<INF && d[k][j]<INF)
			d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
	}
	F(i,n) F(j,n) F(t,n) {
		if (d[i][t]<INF && d[t][t]<0 && d[t][j]<INF)
			d[i][j]=-INF;
	}
	F(i,n) {
		F(j,n)
		{
			if (d[i][j]==INF) cout<<"0 ";else
				if (d[i][j]==-INF) cout<<"2 ";else cout<<"1 ";
		}
		cout<<endl;
	}
}