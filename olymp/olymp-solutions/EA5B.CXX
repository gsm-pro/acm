#include<fstream>

int main() {
	int $;
	std::ifstream("input.txt") >> $;
	std::ofstream("output.txt") << $ / 7 * 2 + $ % 7 / 6 << " " << $ / 7 * 2 + ($ % 7 > 1 ? 2 : $ % 7);
}