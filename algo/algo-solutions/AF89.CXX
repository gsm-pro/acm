#include<iostream>
#include<iomanip>
#include<string>
#include<cmath>
using namespace std;
int n, m, mouseX, mouseY, i, j, dx, dy, nx, ny, row = 0, arow;
double a[404][404];
string s[22];

int main() {
	cin >> n >> m;
	for (i = 0; i < n; i++)	cin >> s[i];
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++) {
			a[i * m + j][i * m + j] = 1;
			if (s[i][j] != '#' && s[i][j] != 'C') {
				if (s[i][j] == 'M') mouseX = i, mouseY = j;
				a[i * m + j][n * m] = 1;
				int w = 0;
				for (dx = -1; dx <= 1; dx++)
					for (dy = -1; dy <= 1; dy++)
						if ((nx = i + dx) >= 0 && (ny = j + dy) >= 0 && nx < n && ny < m && s[nx][ny] != '#')
							w++;
				for (dx = -1; dx <= 1; dx++)
					for (dy = -1; dy <= 1; dy++)
						if ((nx = i + dx) >= 0 && (ny = j + dy) >= 0 && nx < n && ny < m && s[nx][ny] != '#')
							a[i * m + j][nx * m + ny] -= 1. / w;
			}
		}
	for (int col = 0; col < n * m; col++) {
		int cur = row;
		for (i = row + 1; i < n * m; i++) if (abs(a[i][col]) > abs(a[cur][col])) cur = i;
		if (abs(a[cur][col]) < 1e-9) {
			if (mouseX * m + mouseY == col) return cout << "infinity", 0;
			continue;
		}
		swap(a[cur], a[row]);
		for (i = 0; i < n * m; i++) {
			if (i == row) continue;
			double c = a[i][col] / a[row][col];
			for (int j = col; j <= n * m; j++) a[i][j] -= a[row][j] * c;
		}
		if (mouseX * m + mouseY == col) arow = row;
		row++;
	}
	for (j = mouseX * m + mouseY + 1; j < n * m; j++)
		if (abs(a[arow][j]) > 1e-9) return cout << "infinity", 0;
	cout << fixed << setprecision(4) << a[arow][n * m] / a[arow][mouseX * m + mouseY];
}