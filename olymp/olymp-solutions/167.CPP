#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<string>
#include<cmath>
using namespace std;
#define UL unsigned long long
#define set(a,b,w) for (int i=(a);i<=(b);i++) x[i]=w;
#define set1(a,b) for (int i=(a);i<=(b);i++) x[i]=x[i-1]+10000;
#define set2(a,b) for (int i=(a);i<=(b);i++) x[i]=x[i-1]+20000;

bool right(UL x)
{
	char buff[20];
	string s;
	_ui64toa(x*x,buff,10);
	s=buff;
	return (s[0]==s[s.length()-1]);
}

int calc(UL a)
{
	int x[1002];
	x[0]=10320;
	x[1]=18605;
	x[2]=29385;
	x[3]=49386;
	set(4,5,58829);
	x[6]=72338;
	x[7]=85588;
	x[8]=92920;
	x[9]=103183;
	set2(10,13);
	set(14,19,186026);
	set2(20,21);
	x[22]=239632;
	x[23]=249632;
	x[24]=264683;
	x[25]=284683;
	set(26,29,293833);
	set2(30,43);
	set(44,62,588261);
	x[63]=603350;
	set2(64,69);
	x[70]=740456;
	set1(71,76);
	x[77]=815859;
	set2(78,82);
	set(83,93,929179);
	x[94]=931813;
	set2(95,140);
	set(141,199,1860240);
	x[200]=1880240;
	set2(201,222);
	x[223]=2336308;
	set1(224,243);
	x[244]=2546818;
	set2(245,263);
	set(264,299,2938320);
	x[300]=2958320;
	set2(301,446);
	set(447,631,5882592);
	x[632]=5893481;
	set2(633,706);
	x[707]=7384549;
	set1(708,773);
	x[774]=8058582;
	set2(775,835);
	set(836,947,9291782);
	x[948]=9298116;
	set2(949,1001);
	long double z=(long double)a;
	int aa=(int)sqrt(z);
	int ind=aa/100000-1;
	int kol;
	(ind==-1) ? kol=0 : kol=x[ind];
	for (int i=(aa/100000)*100000;i<=aa;i++)
	{
		UL w=i;
		if (right(w)) kol++;
	}
	return kol;
}

int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	UL a,b;
	cin>>a>>b;
	int ans=calc(b)-calc(a);
	long double z=(long double)a;
	UL aa=(UL)sqrt(z);
	if (right(aa) && aa*aa==a) ans++;
	cout<<ans;
}