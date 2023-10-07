import java.io.File;
import java.io.PrintWriter;
import java.math.BigDecimal;
import java.math.MathContext;
import java.util.Scanner;

public class Solution {
    public static BigDecimal WN, W;
    public static boolean stop = false;
    public static final BigDecimal EPS = BigDecimal.valueOf(1e-5);
    public static int N, K, begin = 1, end = 0;
    public static byte V, m;
    public static byte[] queue = new byte[100000];
    public static BigDecimal A[] = new BigDecimal[111];
    public static int[] x = new int[111];
    public static int[] y = new int[111];
    public static BigDecimal[] r = new BigDecimal[111];
    public static boolean[][] G = new boolean[111][111];
    public static boolean[] used = new boolean[111];

    public static void get() {
        V = queue[begin];
        W = A[V];
        begin++;
    }

    public static void put(byte V, BigDecimal W) {
        end++;
        queue[end] = V;
        A[V] = W;
    }

    public static void putAll(int V, BigDecimal W) {
        for (byte i = 1; i <= N; i++) {
            if (G[V][i]) {
                if (x[V] != x[i] || y[V] != y[i]) {
                    WN = W.multiply(r[V]);
                    MathContext mc = MathContext.DECIMAL128;
                    WN = WN.divide(r[i], mc);
                } else {
                    WN = W;
                }
                if (!used[i]) {
                    used[i] = true;
                    put(i, WN);
                } else {
                    stop = A[i].subtract(WN).abs().compareTo(EPS) > 0;
                }
            }
        }
    }

    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("input.txt"));
        PrintWriter out = new PrintWriter(new File("output.txt"));
        N = in.nextInt();
        K = in.nextInt();
        m = in.nextByte();
        for (int i = 1; i <= N; i++) {
            x[i] = in.nextInt();
            y[i] = in.nextInt();
            r[i] = in.nextBigDecimal();
        }
        for (int i = 1; i <= K; i++) {
            int p = in.nextInt();
            int q = in.nextInt();
            G[p][q] = G[q][p] = true;
        }
        for (int i = 1; i <= N; i++) {
            for (int j = i + 1; j <= N; j++) {
                if (x[i] == x[j] && y[i] == y[j]) {
                    G[i][j] = G[j][i] = true;
                }
            }
        }
        used[m] = true;
        put(m, BigDecimal.valueOf(60000.0));
        while (begin <= end && !stop) {
            get();
            putAll(V, W);
        }
        if (stop) {
            out.println("DO NOT TURN IT ON!");
            out.close();
            return;
        }
        for (int i = 1; i <= N; i++) {
            if (!used[i]) {
                out.println("IDLE");
            } else {
                out.println(A[i].add(EPS).toBigInteger().toString());
            }
        }
        in.close();
        out.close();
    }
}