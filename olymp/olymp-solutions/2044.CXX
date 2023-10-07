#include<fstream>

int main() {
	int k, n, a1, a2;
	std::ifstream("input.txt") >> k >> n >> a1 >> a2;
	if (k > a1) a1 = k;
	a1 -= k, a2 -= k;
	std::ofstream("output.txt") << (a2 / n - a1 / n + (a1 % n == 0)) * (0 <= a2);
}