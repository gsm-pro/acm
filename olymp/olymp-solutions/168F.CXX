#include<fstream>

int main() {
	__int64 $, $$, $$$;
	std::ifstream("input.txt") >> $ >> $$ >> $$$;
	std::ofstream("output.txt") << std::max(0LL, ($ + $ + $ + $$ - $$$ + '@' / ' ') / ('@' / ' ' + ' ' / ' '));
}