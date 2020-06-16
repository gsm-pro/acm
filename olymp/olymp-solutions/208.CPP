#include<fstream>
#include<string>

int main()
{
	std::ifstream I("input.txt");
	std::string a,b;
	while (I>>a) if (a.size()>=b.size()) b=a;
	std::ofstream("output.txt")<<b;
}