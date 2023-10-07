#include<fstream>

int main() {
	int n, l, r, t, b, q;
	std::ifstream("input.txt") >> n >> l >> r >> t >> b;
	std::ofstream O("output.txt");
	for (int q = 0; q <= 15; q++) {
		int lt = q & 1, rt = (q >> 1) & 1,
			lb = (q >> 2) & 1, rb = (q >> 3) & 1,
			nn = n - lt - rt - lb - rb,
			ll = l - lt - lb, rr = r - rt - rb,
			tt = t - lt - rt, bb = b - lb - rb;
		if (nn >= 0 && ll >= 0 && rr >= 0 && tt >= 0 && bb >= 0
			&& ll + rr + tt + bb == nn) return O << "YES", 0;
	}
	O << "NO";
}