#include<iostream>
#include<cstdio>
#define LL long long
#define MAXLEN 10
const int Z = 5000001;
int dmulFT[Z], cmulFT[Z], sumFT[Z] = { 0 }, n, m, M, TEN[MAXLEN];

inline int read() {
	int number = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		number = number * 10 + c - '0';
		c = getchar();
	}
	return number;
}

inline void write(int number) {
	bool out = false;
	for (int i = MAXLEN - 1; i >= 0; i--) {
		int digit = number / TEN[i];
		if (out) {
			putchar('0' + digit);
		}
		if (digit > 0 && !out) {
			out = true;
			putchar('0' + digit);
		}
		number %= TEN[i];
	}
	if (!out) {
		puts("0");
	}
	else {
		puts("");
	}
}

inline int h(int i) {
	return i | (i + 1);
}

inline int f(int i) {
	return i & (i + 1);
}

void add(int pos, int val = 1) {
	while (pos <= Z) {
		sumFT[pos] += val, pos = h(pos);
	}
}

int sum(int r) {
	int res = 0;
	while (r > 0) {
		res += sumFT[r], r = f(r) - 1;
	}
	return res;
}

int sum(int l, int r) {
	return sum(r) - sum(l - 1);
}

void direct_mul(int pos, int val) {
	while (pos <= Z) {
		LL val64 = val;
		val64 *= dmulFT[pos];
		val64 %= M;
		dmulFT[pos] = (int)val64;
		if (dmulFT[pos] == 0) {
			dmulFT[pos] = M;
		}
		pos = h(pos);
	}
}

void counter_mul(int pos, int val) {
	pos--;
	while (pos >= 0) {
		LL val64 = val;
		val64 *= cmulFT[pos];
		val64 %= M;
		cmulFT[pos] = (int)val64;
		if (cmulFT[pos] == 0) {
			cmulFT[pos] = M;
		}
		pos = f(pos) - 1;
	}
}

int getProdLR(int l, int r) {
	LL val64 = 1LL;
	int index = l - 1;
	while (h(index) <= r) {
		val64 *= cmulFT[index];
		val64 %= M;
		index = h(index);
	}
	l = index + 1, index = r;
	while (index >= l) {
		val64 *= dmulFT[index];
		val64 %= M;
		index = f(index) - 1;
	}
	return (int)val64;
}

int getProd(int l, int r) {
	if (sum(l, r) != 0) {
		return 0;
	}
	return getProdLR(l, r);
}

void mul(int x, int v) {
	if (v == 0) {
		add(x);
	}
	else {
		direct_mul(x, v);
		counter_mul(x, v);
	}
}

int main() {
	n = 0, TEN[n] = 1;
	while (++n < MAXLEN) {
		TEN[n] = TEN[n - 1] * 10;
	}
	n = read(), m = read(), M = read();
	std::fill(dmulFT, dmulFT + Z, 1);
	std::fill(cmulFT, cmulFT + Z, 1);
	while (m--) {
		int typ = read(), x = read(), y = read();
		(typ == 1) ? mul(x, y % M) : write(getProd(x, y));
	}
}