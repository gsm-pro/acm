import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;

class Solution {
    private static final int MAX_SIZE = 2048;
    private boolean[][] bs;
    private int n;

    public static void main(String[] args) throws Exception {
        new Solution().solve();
    }

    private void solve() throws Exception {
        try (BufferedReader in = new BufferedReader(new FileReader("input.txt"))) {
            n = Integer.parseInt(in.readLine().trim());
            bs = new boolean[n][];
            for (int i = 0; i < n; i++) {
                char[] line = in.readLine().replaceAll(" ", "").toCharArray();
                bs[i] = new boolean[i + 1];
                for (int j = 0; j <= i; j++) {
                    bs[i][j] = line[j] == '+';
                }
            }
        }
        try (BufferedWriter out = new BufferedWriter(new FileWriter("output.txt"))) {
            out.write(Integer.toString(Math.min(tryWith(true), tryWith(false))));
        }
    }

    private int[] B1, B2;

    private void update0(int[] B, int k, int v) {
        for (; k <= MAX_SIZE; k += (k & (-k))) {
            B[k] += v;
        }
    }

    private void update(int i, int j) {
        update0(B1, i, 1);
        update0(B1, j + 1, -1);
        update0(B2, i, i - 1);
        update0(B2, j + 1, -j);
    }

    private int query0(int[] B, int b) {
        int sum = 0;
        for (; b != 0; b -= (b & (-b))) {
            sum += B[b];
        }
        return sum;
    }

    private int query(int b) {
        return query0(B1, b) * b - query0(B2, b);
    }

    private int query(int i, int j) {
        return query(j) - query(i - 1);
    }

    private int tryWith(boolean isToPlus) {
        int ans = 0;
        B1 = new int[MAX_SIZE + 2];
        B2 = new int[MAX_SIZE + 2];
        for (int j = 0; j < n; j++) {
            for (int i = j; i < n; i++) {
                int q = j + n - 1 - i;
                if (bs[i][j] ^ isToPlus ^ (query(q + 1, q + 1) & 1) == 0) {
                    update(j + 1, q + 1);
                    ans++;
                }
            }
        }
        return ans;
    }
}