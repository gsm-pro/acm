#include<fstream>
using namespace std;

int main()
{
	ifstream I("input.txt");
	ofstream O("output.txt");
	int n,c=0,i;
	I>>n;
	if (n<0) n=-n;
	for (i=2;i*i<n;i++) if (n%i==0) ++c;
	(n==0) ? O<<-1 : O<<2*((c<<1)+(i*i==n)+(n>1)+1);
}