#include<fstream>

int main()
{
	int a,b,c,x,y,z;
	std::ifstream("input.txt")>>a>>x>>b>>y>>c>>z;
	std::ofstream("output.txt")<<(a^b^c)<<" "<<(x^y^z);
}