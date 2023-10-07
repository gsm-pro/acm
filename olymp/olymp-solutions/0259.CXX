#include<bits/stdc++.h>
using namespace std;
unordered_map<int, int> hash_table;
int N, i, j, A[3030], Q = 2;

int main() {
	ifstream $("input.txt");
	ofstream $$("output.txt");
	$ >> N;
	for (i = 0; i < N; i++) $ >> A[i];
	if (N <= 2) return $$ << 0, 0;
	vector<vector<int>> dp(N, vector<int>(N, 2));
	for (i = 0; i < N; i++) {
		for (j = i + 1; j < N; j++) {
			int start = A[i] * 2 - A[j];
			if (start < 0 || hash_table.find(start) == hash_table.end()) continue;
			dp[i][j] = dp[hash_table[start]][i] + 1;
			Q = max(Q, dp[i][j]);
		}
		hash_table[A[i]] = i;
	}
	$$ << N - Q;
}