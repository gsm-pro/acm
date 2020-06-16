#include<fstream>

int main()
{
	int k,n,a1,a2;
	std::ifstream("input.txt")>>k>>n>>a1>>a2;
	if (a2>a1 && k>=a1 && k<=a2) a1=k;
	std::ofstream("output.txt")<<((a2-a1)/n+(!((a1-k)%n) || !((a2-k)%n)))*(!(a2<a1 || k>a2));
}