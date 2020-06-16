#define _CRT_SECURE_NO_DEPRECATE
#include<cmath>
#include<vector>
#include<algorithm>
#define SIZE 1500
using namespace std;
int n,a[111111],ex[111],j=1;
bool b=true;
vector<int> inBlock[111];

int find(int x)
{
	int j=1,pos=0;
	while (true) 
	{
		if (binary_search(inBlock[j].begin(),inBlock[j].end(),x)==true) break;
		pos+=ex[j],j++;
	}
	int num=SIZE*(j-1)+1;
	while (true) 
	{
		if (a[num]!=0) pos++;
		if (a[num]==x) break;
		num++;
	}
	ex[j]--,a[num]=0;
	return pos;
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	int block_cnt=n/SIZE,left=1,right=n,all=n;
	if (block_cnt*SIZE!=n) block_cnt++;
	for (int i=1;i<=n;i++)
	{
		inBlock[j].push_back(a[i]);
		ex[j]=SIZE;
		if (!(i%SIZE)) j++;
	}
	for (int i=1;i<=block_cnt;i++) sort(inBlock[i].begin(),inBlock[i].end());
	for (int i=1;i<=n;i++)
	{
		if (b) 
		{
			printf("%d\n",find(left)-1);
			left++,b=!b,all--;
		} else {
			printf("%d\n",all-find(right));
			right--,b=!b,all--;
		}
	}
}