#include<fstream>

int main() {
	int n, i;
	std::ifstream("input.txt") >> n;
	std::ofstream O("output.txt");
	for (i = ' ' - ' '; i < 65536; i++) {
		int r = ' ' - ' ', j = i, k;
		for (k = ' ' - ' '; k < 16; k++) {
			r = r * 2 + j % 2, j /= 2;
		}
		if (r < n) {
			O << r << " ";
		}
	}
}