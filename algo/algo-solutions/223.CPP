#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
	long x1,x2,a,b,c,r;
	int n,k;
	cin>>n>>k>>x1>>x2>>a>>b>>c>>r;
        vector<long long>x(n);
	x[0]=x1;
	x[1]=x2;
	for (int i=2;i<=n-1;i++) x[i]=(a*x[i-2]+b*x[i-1]+c)%r;
	nth_element(x.begin(),x.begin()+k,x.end());
        cout<<x[k-1];
	return 0;
}