import java.io.*;
import java.math.*;

public class Solution {
    static int[][] w = new int[101][101];
    static int[] r = new int[1001];
    static int[] q = new int[1001];
    static int[] c = new int[101];
    static int[] used = new int[101];
    static int n;

    static void dfs1(int x, int col) {
        c[x] = col;
        for (int i = 1; i <= n; i++)
            if (w[x][i] == 1 && c[i] == 0) dfs1(i, (col + 2) % 2 + 1);
    }

    static void dfs2(int v) {
        used[v] = 1;
        for (int i = 1; i <= n; i++)
            if (w[v][i] == 1 && used[i] == 0) dfs2(i);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(
                new FileInputStream("input.txt")));
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter(
                new FileOutputStream("output.txt")));
        String a = in.readLine();
        String[] z = a.split("\\s");
        n = Integer.parseInt(z[0]);
        int m = Integer.parseInt(z[1]);
        for (int i = 1; i <= m; i++) {
            a = in.readLine();
            z = a.split("\\s");
            int v1 = Integer.parseInt(z[0]);
            int v2 = Integer.parseInt(z[1]);
            w[v1][v2] = w[v2][v1] = 1;
            r[i] = v1;
            q[i] = v2;
        }
        for (int i = 1; i <= n; i++)
            if (c[i] == 0) dfs1(i, 1);
        boolean dvud = true;
        for (int i = 1; i <= m; i++)
            if (c[r[i]] == c[q[i]]) dvud = dvud && false;
        int cnt = 0;
        for (int i = 1; i <= n; i++)
            if (used[i] == 0) {
                dfs2(i);
                cnt++;
            }
        BigInteger ans = BigInteger.ZERO;
        if (dvud) ans = BigInteger.valueOf(2).pow(cnt);
        out.write(ans.toString());
        out.close();
    }
}