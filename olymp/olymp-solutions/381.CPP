#include<iostream>
#include<algorithm>
using namespace std;
int a[3];

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>a[0]>>a[1]>>a[2];
	sort(a,a+3);
	if (a[1]-a[0]==a[2]-a[1]) cout<<a[0]<<" "<<a[1]<<" "<<a[2];else cout<<-1;
}