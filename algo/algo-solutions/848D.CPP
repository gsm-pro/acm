#include<iostream>
#include<string>
#include<algorithm>
#include<map>
using namespace std;
#define LL long long
#define SZ 6
map<LL,string> LEFT,RIGHT;
string word;
LL h,p6=1;
int p,maxLen;

void rec(int pos,LL hash)
{
	if (pos==0)
	{
		RIGHT[hash]=word;
		return;
	}
	for (char c='a';c<='j';c++)
	{
		word[pos-1]=c;
		rec(pos-1,hash*p+c);
	}
}

int main()
{
	cin>>h>>p;
	for (int i=1;i<=6;i++) p6*=p;
	for (int maxLen=1;maxLen<=SZ;maxLen++)
	{
		word="";
		for (int j=0;j<maxLen;j++) word+=" ";
		rec(maxLen,0);
	}
	LEFT=RIGHT;
	RIGHT[0]="";
	for (map<LL,string>::iterator it=RIGHT.begin();it!=RIGHT.end();it++)
	{
		LL h2=h-p6*it->first;
		if (LEFT.count(h2)!=0)
		{
			cout<<LEFT[h2]<<it->second;
			return 0;
		}
	}
}