#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<stack>
#include<vector>
using namespace std;
typedef vector<int> LN;
const int B=1000000000;

void add(LN &a,const LN &b)
{
	for (int i=0,c=0;i<(int)max(a.size(),b.size()) || c;++i)
	{
		if (i==(int)a.size()) a.push_back(0);
		a[i]+=c+(i<(int)b.size() ? b[i] : 0);
		if (a[i]<B)
			c=0;
		else
			c=1,a[i]-=B;
	}
}

void subtract(LN &a,const LN &b)
{
	for (int i=0,c=0;i<(int)a.size();++i)
	{
		a[i]-=c+(i<(int)b.size() ? b[i] : 0);
		if (a[i]>=0)
			c=0;
		else
			c=1,a[i]+=B;
	}
	while (a.size() && !a.back()) a.pop_back();
}

void multiply(LN &a,int b)
{
	for (int i=0,c=0;i<(int)a.size() || c;++i)
	{
		if (i==(int)a.size()) a.push_back(0);
		long long cur=a[i]*1ll*b+c;
		c=int(cur/B);
		a[i]=int(cur-c*1ll*B);
	}
	while (a.size() && !a.back()) a.pop_back();
}

int modulus(const LN &a,int b)
{
	int c=0;
	for (int i=(int)a.size()-1;i>=0;--i)
		c=int((a[i]+c*1ll*B)%b);
	return c;
}

int compare(const LN &a,const LN &b)
{
	if (a.size()!=b.size())
		return a.size()<b.size() ? -1 : 1;
	for (int i=(int)a.size()-1;i>=0;--i)
		if (a[i]!=b[i])
			return a[i]<b[i] ? -1 : 1;
	return 0;
}

bool last_neg;

istream & operator >> (istream &stream,LN &a)
{
	static char s[100*1000];
	scanf(" %s",s);
	last_neg=false;
	while (s[0]=='-' || s[0]=='+')
	{
		if (s[0]=='-')
			last_neg=!last_neg;
		memmove(s,s+1,strlen(s));
		if (s[0]==0)
			scanf(" %s",s);
	}
	size_t len=strlen(s);
	if (len%9)
	{
		size_t add=9-len%9;
		memmove(s+add,s,len);
		memset(s,'0',add);
		len+=add;
	}
	for (size_t i=len;i>0;)
	{
		s[i]=0;
		if (i<9)
			i=0;
		else
			i-=9;
		a.push_back(atoi(s+i));
	}
	while (a.size() && !a.back()) a.pop_back();
	return stream;
}

ostream & operator << (ostream &stream,const LN &a)
{
	printf("%d",a.empty() ? 0 : a.back());
	for (int i=(int)a.size()-2;i>=0;--i)
		printf("%09d",a[i]);
	return stream;
}

const int sz=400;
int pr[sz];
int rev[sz][sz];

struct num
{
	short a[sz];

	num()
	{
		memset(a,0,sizeof a);
	}

	num(const LN &num)
	{
		for (int i=0;i<sz;++i)
			a[i]=modulus(num,pr[i]);
	}

	void operator += (const num &rt)
	{
		for (int i=0;i<sz;++i)
		{
			a[i]+=rt.a[i];
			if (a[i]>=pr[i]) a[i]-=pr[i];
		}
	}

	void operator -= (const num &rt)
	{
		for (int i=0;i<sz;++i)
		{
			a[i]-=rt.a[i];
			if (a[i]<0) a[i]+=pr[i];
		}
	}

	void operator *= (const num &rt)
	{
		for (int i=0;i<sz;++i)
			a[i]=((int)a[i]*rt.a[i])%pr[i];
	}

	void negate()
	{
		for (int i=0;i<sz;++i)
			a[i]=a[i] ? pr[i]-a[i] : 0;
	}

	operator LN() const
	{
		LN res,cur(1,1);
		vector<int> x(sz);
		for (int i=0;i<sz;++i)
		{
			x[i]=a[i];
			for (int j=0;j<i;++j)
			{
				x[i]=rev[j][i]*(x[i]-x[j])%pr[i];
				if (x[i]<0) x[i]+=pr[i];
			}
			LN curadd=cur;
			multiply(curadd,x[i]);
			add(res,curadd);
			multiply(cur,pr[i]);
		}
		return res;
	}
};

ostream & operator << (ostream &stream,const num &a)
{
	LN b=a;
	LN t(1,1);
	for (int i=0;i<sz;++i)
		multiply(t,pr[i]);
	subtract(t,b);
	if (compare(t,b)<0)
	{
		printf("-");
		swap(t,b);
	}
	return stream<<b;
}

int powmod(int a,int b,int n)
{
	int res=1;
	while (b)
		if (b&1)
			res=(res*a)%n,--b;
		else
			a=(a*a)%n,b>>=1;
	return res;
}

void calc(stack<num,vector<num>> &st,char op)
{
	if (op<0)
	{
		switch (-op)
		{
			case '+':
				break;
			case '-':
				st.top().negate();
				break;
			case '^':
				st.top()*=st.top();
				break;
		}
	}
	else 
	{
		num rt=st.top();
		st.pop();
		switch (op)
		{
			case '+':
				st.top()+=rt;
				break;
			case '-':
				st.top()-=rt;
				break;
			case '*':
				st.top()*=rt;
				break;
		}
	}
}

int prior(char op)
{
	switch (op)
	{
		case '+':
		case '-':
			return 1;
		case '*':
			return 2;
		case -'+':
		case -'-':
			return 3;
	}
	return 0;
}

int main()
{
	for (int i=2,j=0;j<sz;++i)
	{
		bool prime=true;
		for (int k=0;k<j && pr[k]*pr[k]<=i;++k)
			if (i%pr[k]==0)
			{
				prime=false;
				break;
			}
		if (prime)
			pr[j++]=i;
	}
	for (int i=0;i<sz;++i)
		for (int j=i+1;j<sz;++j)
			rev[i][j]=powmod(pr[i],pr[j]-2,pr[j]);
	int n;
	cin>>n;
	num a[26];
	for (int i=0;i<n;++i)
	{
		LN cur;
		cin>>cur;
		new (&a[i]) num(cur);
		if (last_neg)
			a[i].negate();
	}
	char s[200*1000];
	scanf(" %s",s);
	size_t len=strlen(s);
	stack<num,vector<num>> st;
	((vector<num>&)st).reserve(30*1000*1000/sizeof(num));
	stack<char> opst;
	bool may_unary=true;
	for (size_t i=0;i<len;++i)
	{
		char ch=s[i];
		if (ch>='a' && ch<='z')
		{
			st.push(a[ch-'a']);
			may_unary=false;
		}
		else if (ch=='(' || ch=='[')
		{
			opst.push(ch);
			may_unary=true;
		}
		else if (ch==')' || ch==']')
		{
			while (opst.top()!='(' && opst.top()!='[')
				calc(st,opst.top()),opst.pop();
			opst.pop();
			if (ch==']')
				calc(st,-'^');
			may_unary=false;
		}
		else if (ch=='+' || ch=='-' || ch=='*')
		{
			if (may_unary) ch=-ch;
			while (!opst.empty() && opst.top()!='(' && opst.top()!='[' &&
					(prior(ch)<prior(opst.top()) || ch>0 && prior(ch)==prior(opst.top())))
				calc(st,opst.top()),opst.pop();
			opst.push(ch);
			may_unary=true;
		}
	}
	while (!opst.empty())
		calc(st,opst.top()),opst.pop();
	cout<<st.top();
}