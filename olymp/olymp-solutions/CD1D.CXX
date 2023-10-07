#include<fstream>

int main() {
	__int64 k, s, c = 0, t = 0, i;
	std::ifstream("input.txt") >> k >> s;
	for (i = k + 1; t < s; i++) t += i, c++;
	std::ofstream("output.txt") << (t == s ? k : (s - t + k + 2 * c - 2) / (c - 1) + k);
}