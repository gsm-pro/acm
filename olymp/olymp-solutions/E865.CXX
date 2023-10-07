#include<fstream>
using namespace std;
__int64 N, M, H, I;

int main() {
	ifstream("input.txt") >> N;
	for (M = 1; 10 * M <= 2 * N; M *= 10);
	for (I = 1; I < 10; I++) H += max(0LL, (I * M / 2 - max(1LL, I * M - 1 - N)));
	ofstream("output.txt") << H;
}