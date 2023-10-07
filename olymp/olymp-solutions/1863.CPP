#include<iostream>
#include<string>
using namespace std;

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	string s;
	cin>>s;
	int a=s[0]-'A'+1,b=s[1]-'0';
	int dx[8]={-1,-1,1,1,2,-2,2,-2};
	int dy[8]={2,-2,2,-2,1,-1,-1,1};
	int k=0;
	for (int i=0;i<8;i++)
		if (a+dx[i]>=1 && a+dx[i]<=8 && b+dy[i]>=1 && b+dy[i]<=8) k++;
	cout<<k;
}