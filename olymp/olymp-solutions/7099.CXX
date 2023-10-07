#include<fstream>
int m[40040], n, i, k = ' ' / ' ' + ' ' / ' ';

int main() {
	std::ifstream I("input.txt");
	std::ofstream O("output.txt");
	I >> n;
	while (I >> n) m[n]++;
	for (n = 40004; k; n--)
		for (i = ' ' / ' '; k && i <= (m[n] >> (' ' / ' ')); i++)
			O << n << " ", k--;
}