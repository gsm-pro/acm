#define _CRT_SECURE_NO_DEPRECATE
#include<cstdio>
using namespace std;
enum {MAXLEN=2048};

int main()
{
	unsigned max,spcs,len,cur;
	char s[MAXLEN];
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%u ",&max);
	scanf("%s%n",s,&len),spcs=0,cur=0;
	do 
	{
		if(cur+len<=max)
		{
			cur+=len;
			printf("%*s",cur?len:0,s);
		}
		else if((len-=spcs)<=max)
		{
			cur=len;
			printf("\n%s", s);
		}
		else break;
	} while (scanf(" %n%s%n",&spcs,s,&len)==1);
}