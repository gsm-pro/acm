#include<cstdio>
#define MAXLEN 260
typedef enum {is,add,sub,mult,div,neg,pos} sign;
enum {RG,LF};

struct EXPR
{
	sign OPRT;
	EXPR *LF,*RG;
	char *value;
	EXPR(sign s) 
	{
		OPRT=s,LF=RG=0,value=0;
	};
	EXPR(sign s,EXPR *l,EXPR *r=0) 
	{
		OPRT=s,LF=l,RG=r,value=0;
	};
	EXPR(char *s) 
	{
		OPRT=is,LF=RG=0,value=s;
	};
};

char str[MAXLEN];
char *ptr;
bool BRTS[2][7][7]=
{
	{
		{0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0},
		{0,1,1,0,0,0,0},
		{0,1,1,0,0,0,0},
		{0,1,1,1,1,0,0},
		{0,1,1,0,0,0,0},
		{0,0,0,0,0,0,0}
	},
	{
		{0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0},
		{0,1,1,0,0,0,0},
		{0,1,1,0,0,0,0},
		{0,1,1,0,0,0,0},
		{0,0,0,0,0,0,0}
	}
};

EXPR *calc(int PRIOR=1)
{
	EXPR *res=0,*LF,*RG;
	switch (PRIOR)
	{
		case 1:
			res=LF=calc(2);
			while(1)
				switch(*ptr)
				{
					case '+':
						*ptr=0,++ptr,RG=calc(2);
						LF=res=new EXPR(add,LF,RG);
						break;
					case '-':
						*ptr=0,++ptr,RG=calc(2);
						LF=res=new EXPR(sub,LF,RG);
						break;
					default: return res;
				}
			break;
		case 2:
			res=LF=calc(3);
			while(1)
				switch(*ptr)
				{
					case '*':
						*ptr=0,++ptr,RG=calc(3);
						LF=res=new EXPR(mult,LF,RG);
						break;
					case '/':
						*ptr=0,++ptr,RG=calc(3);
						LF=res=new EXPR(div,LF,RG);
						break;
					default: return res;
				}
			break;
		case 3:
			switch(*ptr)
			{
				case '+': *ptr=0,++ptr;return new EXPR(pos,calc(1));
				case '-': *ptr=0,++ptr;return new EXPR(neg,calc(1));
				case '(': ++ptr;res=calc(1);*ptr=0,++ptr;return res;
				default: 
					res=new EXPR(ptr);
					while(*ptr>='a' && *ptr<='z' || *ptr>='A' && *ptr<='Z') ++ptr;
				return res;
			}
	}
	return 0;
}

void show(EXPR *tree)
{
	char signs[7]={' ','+','-','*','/','-','+'};
	sign cur=tree->OPRT,ls,rs;
	if (cur==is) printf(tree->value);else 
		if (cur<neg)
		{
			ls=tree->LF->OPRT,rs=tree->RG->OPRT;
			if (BRTS[LF][cur][ls]) printf("(");
			show(tree->LF);
			if (BRTS[LF][cur][ls]) printf(")");
			putchar(signs[cur]);
			if (BRTS[RG][cur][rs]) printf("(");
			show(tree->RG);
			if (BRTS[RG][cur][rs]) printf(")");
		}
		else
		{
			putchar(signs[cur]);
			show(tree->LF);
		}
	delete tree;
}

int main()
{
	int n;
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d",&n);
	while (scanf("%s",str)==1)
	{
		ptr=str;
		show(calc());
		puts("");
	}
}