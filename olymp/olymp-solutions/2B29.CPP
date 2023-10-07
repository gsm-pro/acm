#include<fstream>

int main()
{
	int p,n;
	std::ifstream("input.txt")>>n>>p;
	std::ofstream("output.txt")<<n*p;
}