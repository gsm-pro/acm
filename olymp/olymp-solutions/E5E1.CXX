#include<fstream>
int n, a, s, m, w, l;

int main() {
	std::ifstream I("input.txt");
	I >> n >> w;
	while (n--) {
		I >> a;
		s += a;
		if (s > m) m = s;
		if (s < l) l = s;
	}
	std::ofstream("output.txt") << std::max(w - m + 1 + l, 0);
}