import java.util.*;

public class Solution implements Runnable {
    private static final int MAXSIZE = 5005;
    private int[] z = new int[MAXSIZE];

    public static void main(String[] args) {
        new Thread(null, new Solution(), "", 1 << 25).start();
    }

    @Override
    public void run() {
        Arrays.fill(z, -1);
        Scanner in = new Scanner(System.in);
        int A = in.nextInt(), B = in.nextInt(), C = in.nextInt();
        boolean result;
        System.out.print((result = check(A, B, C)) ? "NO" : "YES\n");
        if (!result) {
            for (int i = A - 1; i >= (A >> 1) + (A & 1); i--) {
                out(i, B, C);
            }
            for (int i = B - 1; i >= (B >> 1) + (B & 1); i--) {
                out(A, i, C);
            }
            for (int i = C - 1; i >= (C >> 1) + (C & 1); i--) {
                out(A, B, i);
            }
        }
    }

    private boolean check(int x, int y, int z) {
        return (g(x) ^ g(y) ^ g(z)) == 0;
    }

    private void out(int x, int y, int z) {
        if (check(x, y, z)) {
            System.out.print(String.format("%d %d %d", x, y, z));
            System.exit(0);
        }
    }

    private int g(int n) {
        if (z[n] != -1) {
            return z[n];
        }
        BitSet bs = new BitSet(MAXSIZE);
        for (int i = n - 1; i >= (n >> 1) + (n & 1); i--) {
            bs.set(g(i));
        }
        return z[n] = mex(bs);
    }

    private int mex(BitSet s) {
        for (int i = 0; ; i++) {
            if (!s.get(i)) {
                return i;
            }
        }
    }
}