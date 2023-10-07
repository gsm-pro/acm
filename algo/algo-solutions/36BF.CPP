#include<iostream>
using namespace std;
int dx[8]={-1,-1, 1, 1, 2,-2, 2,-2};
int dy[8]={ 2,-2, 2,-2, 1,-1,-1, 1};
double p[101][8][8];

int main()
{
	int x,y,n;
	cin>>x>>y>>n;
	x--,y--;
	p[0][x][y]=1.0;
	for (int i=1;i<=n;i++)
		for (int x=0;x<8;x++)
			for (int y=0;y<8;y++)
				for (int h=0;h<8;h++)
					if (x+dx[h]>=0 && x+dx[h]<8 && y+dy[h]>=0 && y+dy[h]<8)
						p[i][x][y]+=(p[i-1][x+dx[h]][y+dy[h]]/8.0);
	double res=.0;
	cout.precision(15);
	for (int i=0;i<8;i++)
		for (int j=0;j<8;j++) 
			res+=p[n][i][j];
	cout<<fixed<<res;
}