#include<fstream>
using namespace std;
int a[5005], z[5005][5005], n, k, i, start, ans = 0;

using f_type = int(*)(int);
template<f_type F>
struct f_iter {
	using iterator_category = forward_iterator_tag;
	using difference_type = size_t;
	using value_type = int;
	using pointer = int*;
	using reference = int&;
	int index;
	f_iter(int index) : index(index) {}

	f_iter& operator ++ () {
		++index;
		return *this;
	}

	int operator * () {
		return F(index);
	}

	bool operator != (const f_iter& other) {
		return index != other.index;
	}

	bool operator == (const f_iter& other) {
		return index == other.index;
	}

	bool operator < (const f_iter& other) {
		return index < other.index;
	}
};

template<f_type F>
pair<f_iter<F>, f_iter<F>> f_range(int begin, int end) {
	return { {begin}, {end} };
}

void hamming_init() {
	for (int shift = 0; shift < n; shift++)
		for (int len = 1; len <= n; len++)
			if (shift + len <= n)
				z[shift][len] = z[shift][len - 1] + (a[shift + len - 1] != a[len - 1]);
}

inline int hamming_query(int len, int pos1, int pos2) {
	return z[pos2 - pos1][pos1 + len] - z[pos2 - pos1][pos1];
}

int is_failed_check_rg(int len) {
	for (int start_search = start + len; start_search <= n - len; start_search++)
		if (hamming_query(len, start, start_search) <= k) return 0;
	return 1;
}

int is_failed_check_lf(int len) {
	for (int start_search = 0; start_search <= start - len; start_search++)
		if (hamming_query(len, start_search, start) <= k) return 0;
	return 1;
}

int search_len_rg(int maxlen_rg) {
	if (is_failed_check_rg(1) == 1) return -1;
	if (is_failed_check_rg(maxlen_rg) == 0) return maxlen_rg;
	auto rg = f_range<is_failed_check_rg>(1, maxlen_rg);
	return lower_bound(rg.first, rg.second, 1).index - 1;
}

int search_len_lf(int maxlen_lf) {
	if (is_failed_check_lf(1) == 1) return -1;
	if (is_failed_check_lf(maxlen_lf) == 0) return maxlen_lf;
	auto lf = f_range<is_failed_check_lf>(1, maxlen_lf);
	return lower_bound(lf.first, lf.second, 1).index - 1;
}

int main() {
	ifstream I("input.txt");
	I >> n >> k;
	for (i = 0; i < n; i++) I >> a[i];
	hamming_init();
	for (start = 0; start <= n - 1; start++) {
		int found_len_rg = search_len_rg((n - start) / 2),
			found_len_lf = search_len_lf(min(start, n - start));
		if (found_len_lf > 0 || found_len_rg > 0)
			ans += max(found_len_lf, found_len_rg);
	}
	ofstream("output.txt") << ans;
}