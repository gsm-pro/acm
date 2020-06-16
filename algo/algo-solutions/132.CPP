#include<iostream>
#include<string>
using namespace std;
string s[10001];
int num[10001],ans[10001],n;

void siftDown(int ind) 
{
	int indMax=ind;
	if (ind*2<=n && s[ind*2]>s[indMax]) indMax=ind*2;
	if (ind*2+1<=n && s[ind*2+1]>s[indMax]) indMax=ind*2+1;
	if (indMax!=ind) 
	{
		swap(s[ind],s[indMax]);
		swap(ans[num[ind]],ans[num[indMax]]);
		swap(num[ind],num[indMax]);
		siftDown(indMax);
	}
}

int main() 
{
	cin>>n;
	for (int i=1;i<=n;i++) 
	{ 
		cin>>s[i];
		num[i]=i; 
		ans[i]=i;
	}
	for (int i=n/2;i>0;i--) siftDown(i);
	for (int i=1;i<=n;i++) cout<<ans[i]<<"\n";
}