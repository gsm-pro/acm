#include<vector>
#include<iostream>
#include<string>
using namespace std;
double a[26];
int k;

bool letter(char a)
{
	return (a>='a') && (a<='z');
}

int ord(char a)
{
	return (int)a-(int)'a';
}

bool sogl(char a)
{
	return !((a=='a') || (a=='e') || (a=='i') || (a=='o') || (a=='u'));

}

char chr(int a)
{
	return (char)(a+(int)'a');
}

char shift(char a,int p)
{
	int d=ord(a);
	d=(d+p)%26;
	return chr(d);
}

int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	string s;
	a[0]=0.08216886;
	a[1]=0.01414543;
	a[2]=0.02222407;
	a[3]=0.04738307;
	a[4]=0.12691675;
	a[5]=0.02157211;
	a[6]=0.02067983;
	a[7]=0.06571401;
	a[8]=0.06321329;
	a[9]=0.00078166;
	a[10]=0.00871759;
	a[11]=0.04129980;
	a[12]=0.02507745;
	a[13]=0.06897036;
	a[14]=0.07887130;
	a[15]=0.01506937;
	a[16]=0.00086235;
	a[17]=0.05780150;
	a[18]=0.06144739;
	a[19]=0.09049823;
	a[20]=0.02974358;
	a[21]=0.00938387;
	a[22]=0.02501542;
	a[23]=0.00137420;
	a[24]=0.02059004;
	a[25]=0.00047845;
	cin>>s;
	string ns;
	ns.resize(s.length());
	int p,q;
	vector<double> patt;
	double minmist=1000000000;
	for(int i=0;i<26;i++)
	{
		for(int j=0;j<26;j++)
		{
			int bad=0;
			patt.assign(26,0);
			for(int k=0;k<s.length();k++)
				if (k&1)
					ns[k]=shift(s[k],i);
				else
					ns[k]=shift(s[k],j);
			double mistake=0;
			for(int k=0;k<s.length();k++)
				patt[ord(ns[k])]++;
			for(int k=0;k<26;k++)
				patt[k]/=s.length();
			for(int k=0;k<26;k++)
				mistake+=(patt[k]-a[k])*(patt[k]-a[k]);
			for(int i=3;i<ns.length();i++)
			{
				if ((sogl(ns[i-3]))&&(ns[i-2])&&(ns[i-1])&&(ns[i])) bad+=2;
				if ((!sogl(ns[i-3]))&&(!sogl(ns[i-2]))&&(!sogl(ns[i-1]))&&(!sogl(ns[i]))) bad++;
				if ((ns[i]=='d')&&(ns[i-1]=='e')) bad--;
				if ((ns[i-2]=='i')&&(ns[i-1]=='n')&&(ns[i]=='g')) bad-=3;
				if (i>3)
					if ((sogl(ns[i-4]))&&(sogl(ns[i-3]))&&(sogl(ns[i-2]))&&(sogl(ns[i-1]))&&(sogl(ns[i]))) bad+=5;
			}
			mistake=max(bad,0)+mistake;
			if (mistake<minmist)
			{
				p=i;
				q=j;
				minmist=mistake;
			}
		}
	}
	ns=s;
	for(int i=0;i<s.length();i++)
		if (i&1)
			ns[i]=shift(s[i],p);
		else
			ns[i]=shift(s[i],q);
	cout<<ns;
}