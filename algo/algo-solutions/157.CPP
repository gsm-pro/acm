#include<iostream>
#include<vector>
using namespace std;
#define PII pair<int,int>
#define sqr(x) (x)*(x)
#define dst(z1,z2) sqr(z2.x-z1.x)+sqr(z2.y-z1.y)
#define x first
#define y second

int main()
{
	int n,m=0,k=0,q;
	cin>>n;
	vector<PII> a(n),b;
	for (int i=0;i<n;i++) cin>>a[i].x>>a[i].y;
	for (int i=1;i<n;i++)
		if (a[i].y<a[m].y || (a[i].y==a[m].y && a[i].x>a[m].x)) m=i;
	b.push_back(a[m]);
	a[m]=a[0],a[0]=b[0],m=1;
	while (n!=1)
	{
		for (int j=1;j<n;j++)
		{
			q=(a[m].x-b[k].x)*(a[j].y-b[k].y)-(a[j].x-b[k].x)*(a[m].y-b[k].y);
			if (q<0 || (q==0 && dst(b[k],a[m])<dst(b[k],a[j]))) m=j;
		}
		b.push_back(a[m]);
		k++,m=0;
		if (b[k].x==b[0].x && b[k].y==b[0].y) break;
	}
	double s=0;
	for (int i=1;i<(int)b.size()-1;i++) 
		s+=.5*abs((b[i].x-b[0].x)*(b[i+1].y-b[0].y)-(b[i+1].x-b[0].x)*(b[i].y-b[0].y));
	cout<<fixed<<s;
}