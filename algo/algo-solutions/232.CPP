#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<map>
#include<bitset>
#include<vector>
using namespace std;
#define BLOCKSIZE 8000
#define SMALL_BLOCK_SIZE 31
#define SMALL_BLOCK_COUNT 260

struct bitline {
	unsigned int v[SMALL_BLOCK_COUNT];
};

void inline operator |= (bitline &a, bitline &b) {
	for (int i = 1; i < SMALL_BLOCK_COUNT; i++) a.v[i] |= b.v[i];
}

void inline bitline_set(bitline &a, int pos) {
	int blockNum = (pos / SMALL_BLOCK_SIZE) + 1;
	int positionInBlock = pos - (blockNum - 1) * SMALL_BLOCK_SIZE;
	a.v[blockNum] |= (1 << pos);
}

int inline bitline_getInBlock(bitline &a, int blockNum, int pos) {
	return a.v[blockNum] & (1 << pos);
}

int inline bitline_getOnesInBlock(bitline &a, int blockNum) {
	return a.v[blockNum] == 0 ? 0 : __popcnt(a.v[blockNum]);
}

int inline bitline_getPositionOfKth(bitline &a, int kth) {
	int blockNumberWithMiddleMinimum = 0, qtyOfProcessedMinimums = 0;
	while (true) {
		int ones = bitline_getOnesInBlock(a, blockNumberWithMiddleMinimum);
		if (qtyOfProcessedMinimums + ones < kth) {
			blockNumberWithMiddleMinimum++;
			qtyOfProcessedMinimums += ones;
		}
		else break;
	}
	int positionOfMiddleMinimum = (blockNumberWithMiddleMinimum - 1) * SMALL_BLOCK_SIZE;
	int smallBlockNumber = positionOfMiddleMinimum / SMALL_BLOCK_SIZE + 1;
	int bitPosition = 0;
	for (; bitPosition <= SMALL_BLOCK_SIZE; bitPosition++) {
		if (bitline_getInBlock(a, smallBlockNumber, positionOfMiddleMinimum + bitPosition)) {
			qtyOfProcessedMinimums++;
			if (qtyOfProcessedMinimums == kth) {
				return positionOfMiddleMinimum + bitPosition;
			}
		}
	}
}

int inline bitline_getOnes(bitline &a) {
	int result = 0;
	for (int i = 0; i < SMALL_BLOCK_COUNT; i++) {
		result += bitline_getOnesInBlock(a, i);
	}
	return result;
}

void inline bitline_reset(bitline &a, int pos) {
	int blockNum = (pos / SMALL_BLOCK_SIZE) + 1;
	int positionInBlock = pos - (blockNum - 1) * SMALL_BLOCK_SIZE;
	a.v[blockNum] ^= (1 << pos);
}

vector<int> fenwick_t;
int fenwick_n;
void fenwick_init(int size) {
	fenwick_n = size;
	fenwick_t.assign(fenwick_n, 0);
}

int fenwick_sum(int r) {
	int result = 0;
	for (; r >= 0; r = (r & (r + 1)) - 1) result += fenwick_t[r];
	return result;
}

void fenwick_inc(int p) {
	for (; p < fenwick_n; p = (p | (p + 1))) fenwick_t[p] += 1;
}

int main() {
	unsigned int n, a;
	scanf("%d", &n);
	vector<map<unsigned int, bitline>> number2positionInBlock;
	number2positionInBlock.resize(n / BLOCKSIZE + 3);
	map<unsigned int, int> number2qtyTotal;
	int totalBlockCount = 0;
	fenwick_init(50005);
	for (unsigned int i = 1; i <= n; i++) {
		scanf("%d", &a);
		number2qtyTotal[a]++;
		int blockNum = (i / BLOCKSIZE) + 1;
		int positionInBlock = i - (blockNum - 1) * BLOCKSIZE;
		bitline_set(number2positionInBlock[blockNum][a], positionInBlock);
		totalBlockCount = blockNum;
	}
	for (unsigned int iterNumber = 1; iterNumber <= n; iterNumber++) {
		map<unsigned int, int>::iterator it = number2qtyTotal.begin();
		int currentMinimum = it->first;
		int minimumCount = it->second;
		int numberOfMiddleMinimumElement = (minimumCount + 1) >> 1;
		int blockNumberWithMiddleMinimum = 0, qtyOfProcessedMinimums = 0;
		while (true) {
			int ones = bitline_getOnes(number2positionInBlock[blockNumberWithMiddleMinimum][currentMinimum]);
			int sum = qtyOfProcessedMinimums + ones;
			if (sum < numberOfMiddleMinimumElement) {
				blockNumberWithMiddleMinimum++;
				qtyOfProcessedMinimums = sum;
			}
			else break;
		}
		int positionOfMiddleMinimum = (blockNumberWithMiddleMinimum - 1) * BLOCKSIZE;
		int bitlinePosition =
			bitline_getPositionOfKth(number2positionInBlock[blockNumberWithMiddleMinimum][currentMinimum],
				numberOfMiddleMinimumElement - qtyOfProcessedMinimums);
		positionOfMiddleMinimum += bitlinePosition;
		printf("%d ", positionOfMiddleMinimum - fenwick_sum(positionOfMiddleMinimum));
		fenwick_inc(positionOfMiddleMinimum);
		int m = number2qtyTotal[currentMinimum] - 1;
		if (m > 0) {
			int s = currentMinimum + iterNumber;
			number2qtyTotal[s] += m;
			bitline_reset(number2positionInBlock[blockNumberWithMiddleMinimum][currentMinimum], bitlinePosition);
			for (int block = 1; block <= totalBlockCount; block++) {
				if (bitline_getOnes(number2positionInBlock[block][currentMinimum]) > 0) {
					number2positionInBlock[block][s] |= number2positionInBlock[block][currentMinimum];
				}
				number2positionInBlock[block].erase(currentMinimum);
			}
		}
		else
			for (int block = 1; block <= totalBlockCount; block++) {
				number2positionInBlock[block].erase(currentMinimum);
			}
		number2qtyTotal.erase(currentMinimum);
	}
}