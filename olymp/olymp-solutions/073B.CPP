#include<fstream>

int main()
{
	int n,k=0;
	std::ifstream("input.txt")>>n;
	for (int i=1;i<n;i++) k+=(i%2);
	std::ofstream("output.txt")<<k;
}