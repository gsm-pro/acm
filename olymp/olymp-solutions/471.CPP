#include<iostream>
#include<string>
using namespace std;
int n,res=999,qx[8],qy[8],col[8];
bool isOccupied[8],isAttacked[8];
string position;

void searchMinimalPath(int num,int sum)
{
	if (num==n)
	{
		res=min(res,sum);
		return;
	}
	for (int i=0;i<n;i++)
	{
		if (!isOccupied[i])
		{
			isOccupied[i]=true;
			searchMinimalPath(num+1,sum+max(abs(qx[num]-i),abs(qy[num]-col[i])));
			isOccupied[i]=false;
		}
	}
}

void searchFinishPositions(int row)
{
	if (row==n)
	{
		for (int i=0;i<n;i++)
			for (int j=i+1;j<n;j++)
				if (abs(i-j)==abs(col[i]-col[j])) return;
		searchMinimalPath(0,0);
	}
	for (int c=0;c<n;c++)
	{
		if (!isAttacked[c])
		{
			isAttacked[c]=true;
			col[row]=c;
			searchFinishPositions(row+1);
			isAttacked[c]=false;
		}
	}
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>n;
	for (int i=0;i<n;i++)
	{
		cin>>position;
		qx[i]=position[0]-'a';
		qy[i]=position[1]-'1';
	}
	searchFinishPositions(0);
	cout<<(res<999 ? res : -1);
}