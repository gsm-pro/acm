#include<fstream>
using namespace std;
int a, b, c, d, e, f, d1Type, $ = 0;

int main() {
	ifstream("input.txt") >> a >> b >> c >> d >> e >> f;
	for (d1Type = 0; d1Type <= d; d1Type++)
		$ = max($, min(a, d1Type) * e + min(d - d1Type, min(b, c)) * f);
	ofstream("output.txt") << $;
}