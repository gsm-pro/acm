import java.math.BigInteger;
import java.util.Scanner;

public class Solution {
    private static BigInteger[] F = new BigInteger[61];

    private static BigInteger C(int n, int k) {
        if (n - k < 0) {
            return BigInteger.ZERO;
        }
        return (F[n].divide(F[k])).divide(F[n - k]);
    }

    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(System.in);
        F[0] = BigInteger.ONE;
        F[1] = BigInteger.ONE;
        for (int i = 2; i <= 60; i++)
            F[i] = F[i - 1].multiply(BigInteger.valueOf(i));
        int r = in.nextInt(), g = in.nextInt(), b = in.nextInt();
        System.out.print(C(r + g, g).multiply(C(r + g + 1, b)).toString());
    }
}