#include<bits/stdc++.h>

int main() {
	__int64 $, $$, $$$ = 1LL;
	std::ifstream("input.txt") >> $ >> $$;
	while ($ % $$) $$$++, $ -= $ / $$;
	std::ofstream("output.txt") << $$$;
}