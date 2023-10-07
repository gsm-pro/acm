#include<fstream>
#define LL long long
const LL INF = (LL)1e16;

LL gcd(LL a, LL b) {
	for (; b; b ^= a ^= b ^= a %= b);
	return a;
}

LL st(LL b, LL d) {
	LL v = b;
	for (LL i = 1, a = b; a <= d && d % a == 0; i++) {
		v = a, a *= b;
	}
	return v;
}

LL ntype(LL b, LL d, LL& res) {
	LL g = gcd(b, d);
	if (g > 1) {
		for (LL i = 1, a = g; a < INF; i++, a *= g) {
			if (a % d == 0) {
				res = i;
				return 2;
			}
		}
	}
	if (b % d == 1) {
		return 3;
	}
	if ((b + 1) % d == 0) {
		return 11;
	}
	return 0;
}

int main() {
	LL b, d;
	std::ifstream("input.txt") >> b >> d;
	std::ofstream O("output.txt");
	LL res, tp = ntype(b, d, res);
	if (tp > 0) {
		O << tp << "-type";
		if (tp == 2) {
			O << "\n" << res;
		}
		return 0;
	}
	for (LL i = 2; i <= d; ++i) {
		if (d % i == 0) {
			if (ntype(b, st(i, d), res) > 0) {
				d /= st(i, d);
			}
		}
	}
	if (d == 1) {
		O << "6-type";
		return 0;
	}
	O << "7-type";
}