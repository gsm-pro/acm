#include<bits/stdc++.h>
using namespace std;
map<int, int> $;

int main() {
	ifstream $$$$("input.txt");
	for (int $$$ = ' ' - ' ', $$; $$$ < 9; $$$++) {
		$$$$ >> $$;
		$[$$$ / 3] += ($$ * ($$ > ' ' - ' '));
	}
	ofstream("output.txt") << max($[0], max($[1], $[2])) - ($[0] ^ $[1] ^ $[2]);
}