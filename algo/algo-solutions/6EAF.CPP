#include<iostream>
#include<vector>
using namespace std;
#define inf (int)2e9
#define LL long long
vector<pair<LL,LL>> segm;
int n,k;

LL getNum(LL x)
{
	LL result=0;
	for (int i=0;i<n;i++)
	{
		if (x>=segm[i].second) result+=(segm[i].second-segm[i].first+1LL);else
			if (x>=segm[i].first) result+=(x-segm[i].first+1LL);
	}
	return result;
}

int main()
{
	cin>>n>>k;
	segm.resize(n);
	k++;
	for (int i=0;i<n;i++) cin>>segm[i].first>>segm[i].second;
	LL lf=-inf-2,rg=inf+2,m;
	while (lf<=rg)
	{
		m=(lf+rg)>>1;
		LL count=getNum(m),count1=getNum(m+1);
		if (count<k && count1>=k) break;
		if (count>=k) rg=m-1;
		if (count1<k) lf=m+1;
	}
	cout<<m+1;
}