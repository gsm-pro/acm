#include<fstream>

int main()
{
	double a,b;
	std::ifstream("input.txt")>>a>>b;
	std::ofstream("output.txt")<<((int)b-(b<0 && b!=(int)b)-(int)a-(a>0 && a!=(int)a)+1)*(a<=b);
}