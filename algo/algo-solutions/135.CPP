#define _CRT_SECURE_NO_DEPRECATE
#include<set>
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;
int c[100001],cnt[100001],n;
set<int> S;
vector<int> G[100001];

int main() 
{
	scanf("%d",&n);
	for (int i=0;i<n-1;i++)
	{
		scanf("%d",&c[i]);
		cnt[--c[i]]++;
	}
	for (int i=0;i<n;i++) 
		if (cnt[i]==0) S.insert(i);
	for (int i=0;i<n-1;i++) 
	{
		int num=c[i];
		G[num].push_back(*S.begin());
		G[*S.begin()].push_back(num);
		S.erase(S.begin());
		cnt[num]--;
		if (cnt[num]==0) S.insert(num);
	}
	for (int i=0;i<n;i++) 
	{
		sort(G[i].begin(),G[i].end());
		for (int j=0;j<(int)G[i].size();j++) printf("%d ",G[i][j]+1);
		printf("0\n");
	}
}