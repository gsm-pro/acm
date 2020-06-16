#include<iostream>
using namespace std;
int z[51][51][51],n;

int rec(int a, int b, int c)
{
	if (z[a][b][c]!=-1) return z[a][b][c];
	if (a+b+c==0) return 0;
	z[a][b][c]=1<<20;
	for (int i=0;i<a;i++)
		z[a][b][c]=min(z[a][b][c],max(rec(a-i-1,b,c),rec(i,0,b+c)));
	for (int i=0;i<b;i++)
		z[a][b][c]=min(z[a][b][c],max(rec(0,b-i-1,c),rec(a,i,b+c-i)));
	for (int i=0;i<b;i++)
		z[a][b][c]=min(z[a][b][c],max(rec(a+i+1,b-i-1,c),rec(a,i,0)));
	for (int i=0;i<c;i++)
		z[a][b][c]=min(z[a][b][c],max(rec(a+b,0,c-i-1),rec(a,b,i)));
	z[a][b][c]++;
	return z[a][b][c];
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>n;
	memset(z,255,sizeof(z));
	cout<<rec(0,n,0);
}