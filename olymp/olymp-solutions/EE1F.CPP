#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define all(v) v.begin(),v.end()

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	vector<int> a(3),b(3);
	cin>>a[0]>>a[1]>>a[2]>>b[0]>>b[1]>>b[2];
	sort(all(a));
	sort(all(b));
	cout<<a[0]*b[0]+a[1]*b[1]+a[2]*b[2];
}