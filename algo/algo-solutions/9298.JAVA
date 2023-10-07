import java.util.Scanner;

public class Solution {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int N = in.nextInt();
        long X = in.nextLong(), Y = in.nextLong(), A = in.nextLong(),
                B = in.nextLong(), C = in.nextLong(), S = in.nextLong();
        long[] D = new long[N];
        long b = S;
        for (int i = 0; i < N; i++) {
            b = (A * b + B) % C;
            D[i] = X * b + Y;
        }
        long[] P = new long[N];
        P[0] = D[0];
        for (int i = 1; i < N; i++) {
            P[i] = P[i - 1] + D[i];
        }
        long[] Q = new long[N];
        Q[N - 1] = P[N - 1];
        for (int i = N - 2; i >= 0; i--) {
            Q[i] = Math.max(Q[i + 1], P[i]);
        }
        int P1 = 0, P2 = 0, maxLen = -1;
        long curSum;
        int[] RES = new int[]{-1, -1};
        while (P1 < N && P2 < N) {
            curSum = P1 > 0 ? Q[P2] - P[P1 - 1] : Q[P2];
            if (curSum > 0) {
                if (P2 - P1 > maxLen) {
                    maxLen = P2 - P1;
                    RES[0] = P1;
                    RES[1] = P2;
                }
                P2++;
            } else {
                P1++;
            }
        }
        RES[0]++;
        RES[1]++;
        int start = RES[0], len = RES[1] - RES[0] + 1;
        System.out.println(start + " " + len);
    }
}