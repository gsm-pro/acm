#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>

struct POINT {
	int x, y;
};

class LIST {
public:
	LIST *next;
	POINT v;
	LIST(POINT tv) : v(tv) {
		next = 0;
	}
};

class QUEUE {
public:
	LIST *first, *last;
	int size;

	QUEUE() {
		reset();
	}

	void reset() {
		first = last = 0;
		size = 0;
	}

	void pb(POINT v) {
		if (first) {
			last = last->next = new LIST(v);
		}
		else {
			first = last = new LIST(v);
		}
		size++;
	}

	POINT pop() {
		POINT fv = first->v;
		LIST *t = first;
		size--;
		first = first->next;
		delete t;
		return fv;
	}
};

const int MAXN = 5001;
const int MAXCELL = 2501;
const int dx[4] = { -1, 1, 0, 0 };
const int dy[4] = { 0, 0, -1, 1 };
POINT w1, w2;
POINT P[MAXN];
POINT *PP[MAXN];
unsigned char cell_g[MAXCELL][MAXCELL], cell_msk[MAXCELL][MAXCELL];
int M, M_X, M_Y, minx, miny, maxx, maxy, ANS;
QUEUE PQ;

inline void setMsk(int i, int j, int bit) {
	cell_msk[i][j] |= (1 << bit);
}

inline bool getMsk(int i, int j, int bit) {
	return ((cell_msk[i][j] >> bit) & 1) != 0;
}

void read() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	std::cin >> w1.x >> w1.y >> w2.x >> w2.y;
	int tmp = w1.y;
	w1.y = w2.y;
	w2.y = tmp;
	std::cin >> M;
	for (int i = 1; i <= M; i++) {
		std::cin >> P[i].x >> P[i].y;
		PP[i] = &P[i];
	}
	PP[M + 1] = &w1;
	PP[M + 2] = &w2;
}

int cmp1(const void *a, const void *b) {
	return (*(POINT**)a)->x - (*(POINT**)b)->x;
}

int cmp2(const void *a, const void *b) {
	return (*(POINT**)a)->y - (*(POINT**)b)->y;
}

void disp() {
	int last = -1, k = -1;
	qsort(PP + 1, M + 2, sizeof(PP[0]), cmp1);
	for (int i = 1; i <= M + 2; i++) {
		if (PP[i]->x > last) {
			last = PP[i]->x;
			M_X = ++k;
		}
		PP[i]->x = k;
	}
	last = -1, k = -1;
	qsort(PP + 1, M + 2, sizeof(PP[0]), cmp2);
	for (int i = 1; i <= M + 2; i++) {
		if (PP[i]->y > last) {
			last = PP[i]->y;
			M_Y = ++k;
		}
		PP[i]->y = k;
	}
}

void draw(POINT a, POINT b) {
	if (a.y == b.y) {
		int j = a.y + 1;
		if (b.x > a.x) {
			for (int i = a.x + 1; i <= b.x; i++) {
				if (j <= M_Y) {
					setMsk(i, j, 2);
				}
				if (j - 1 >= 1) {
					setMsk(i, j - 1, 3);
				}
			}
		}
		else {
			for (int i = b.x + 1; i <= a.x; i++) {
				if (j <= M_Y) {
					setMsk(i, j, 2);
				}
				if (j - 1 >= 1) {
					setMsk(i, j - 1, 3);
				}
			}
		}
	}
	else {
		int i = a.x + 1;
		if (b.y > a.y) {
			for (int j = a.y + 1; j <= b.y; j++) {
				if (i <= M_X) {
					setMsk(i, j, 0);
				}
				if (i - 1 >= 1) {
					setMsk(i - 1, j, 1);
				}
			}
		}
		else {
			for (int j = b.y + 1; j <= a.y; j++) {
				if (i <= M_X) {
					setMsk(i, j, 0);
				}
				if (i - 1 >= 1) {
					setMsk(i - 1, j, 1);
				}
			}
		}
	}
}

void graph() {
	for (int i = 2; i <= M; i++) {
		draw(P[i - 1], P[i]);
	}
	draw(P[M], P[1]);
}

inline bool inRange(int x, int y) {
	return x >= 1 && x <= M_X && y >= 1 && y <= M_Y;
}

inline bool inWindow(int x, int y) {
	return x >= minx && x <= maxx && y >= miny && y <= maxy;
}

bool fill(int tx, int ty, unsigned char C) {
	PQ.reset();
	POINT i;
	i.x = tx;
	i.y = ty;
	PQ.pb(i);
	bool GRAY = true;
	while (PQ.size) {
		i = PQ.pop();
		cell_g[i.x][i.y] = C;
		for (int k = 0; k < 4; k++) {
			if (!getMsk(i.x, i.y, k)) {
				POINT j;
				j.x = i.x + dx[k];
				j.y = i.y + dy[k];
				if (inRange(j.x, j.y)) {
					if (cell_g[j.x][j.y] == 0) {
						cell_g[j.x][j.y] = C;
						PQ.pb(j);
					}
				}
				else {
					GRAY = false;
				}
			}
		}
	}
	return GRAY;
}

unsigned char getG() {
	unsigned char C = 0;
	for (int i = 1; i <= M_X; i++) {
		for (int j = 1; j <= M_Y; j++) {
			if (cell_g[i][j] == 0) {
				C++;
				if (fill(i, j, C)) {
					return C;
				}
			}
		}
	}
	return 0;
}

void fill2(int tx, int ty, unsigned char R) {
	PQ.reset();
	POINT i;
	i.x = tx;
	i.y = ty;
	PQ.pb(i);
	while (PQ.size) {
		i = PQ.pop();
		cell_g[i.x][i.y] = 0;
		for (int k = 0; k < 4; k++) {
			if (!getMsk(i.x, i.y, k)) {
				POINT j;
				j.x = i.x + dx[k];
				j.y = i.y + dy[k];
				if (inWindow(j.x, j.y)) {
					if (cell_g[j.x][j.y] == R) {
						cell_g[j.x][j.y] = 0;
						PQ.pb(j);
					}
				}
			}
		}
	}
}

void solve(unsigned char R) {
	ANS = 0;
	minx = w1.x + 1;
	maxx = w2.x;
	miny = w1.y + 1;
	maxy = w2.y;
	for (int i = minx; i <= maxx; i++) {
		for (int j = miny; j <= maxy; j++) {
			if (cell_g[i][j] == R) {
				ANS++;
				fill2(i, j, R);
			}
		}
	}
}

int main() {
	std::cin.tie(0);
	std::cout.tie(0);
	std::ios_base::sync_with_stdio(0);
	read();
	disp();
	graph();
	solve(getG());
	std::cout << ANS;
}