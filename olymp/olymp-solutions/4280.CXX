#define _CRT_SECURE_NO_DEPRECATE
#include<cstdio>
int c[32], t[32], i, j, l;
char s[5120], k;

bool o(char* s) {
	for (k = 27; k--; t[k] = c[k]);
	for (k = 26; *s; ++s, --t[k]) {
		for (; k && !t[k]; --k);
		if (k != *s) return k < *s;
	}
	for (; k && !t[k]; --k);
	return !k;
}

int main() {
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
	for (gets(s); s[l]; ++l) c[s[l] - 96]++;
	for (gets(s); s[i]; ++i) s[i] -= 96;
	if (o(s)) return puts("-1"), 0;
	for (i = 0; i < l && s[i]; ++i) {
		for (j = s[i]; !c[j]; ++j); --c[j];
		if (j > s[i]) {
			putchar(j + 96);
			break;
		}
		if (o(s + i + 1)) {
			++c[j];
			for (++j; !c[j]; ++j);
			--c[j];
		}
		putchar(j + 96);
		if (j > s[i]) break;
	}
	for (i = 1; i < 27; ++i)
		for (; c[i]--;) putchar(i + 96);
}