import java.math.*;
import java.util.*;

public class Solution {
    static BigInteger[] F = new BigInteger[51];
    static BigInteger[] GRAF = new BigInteger[51];
    static BigInteger[][] CNK = new BigInteger[51][51];

    static public BigInteger G(int n) {
        return BigInteger.valueOf(2).pow(n * (n - 1) / 2);
    }

    static public BigInteger C(int n, int k) {
        return (F[n].divide(F[k])).divide(F[n - k]);
    }

    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(System.in);
        F[0] = BigInteger.ONE;
        F[1] = BigInteger.ONE;
        for (int i = 2; i <= 50; i++)
            F[i] = F[i - 1].multiply(BigInteger.valueOf(i));
        for (int i = 1; i <= 50; i++)
            GRAF[i] = G(i);
        for (int i = 0; i <= 50; i++)
            for (int j = i; j <= 50; j++)
                CNK[i][j] = C(j, i);
        BigInteger[] kol = new BigInteger[201];
        kol[1] = BigInteger.ONE;
        for (int i = 2; i <= 50; i++) {
            BigInteger sum = BigInteger.ZERO;
            for (int k = 1; k <= i - 1; k++)
                sum = sum.add((BigInteger.valueOf(k).multiply(CNK[k][i]))
                        .multiply(kol[k].multiply(GRAF[i - k])));
            kol[i] = GRAF[i].subtract(sum.divide(BigInteger.valueOf(i)));
        }
        int n = in.nextInt();
        int k = in.nextInt();
        BigInteger d[][] = new BigInteger[51][51];
        for (int i = 0; i < 51; i++)
            for (int j = 0; j < 51; j++)
                d[i][j] = BigInteger.ZERO;
        d[0][0] = BigInteger.ONE;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= i && j <= k; ++j)
                for (int s = 1; s <= i; s++)
                    d[i][j] = d[i][j].add((CNK[s - 1][i - 1].multiply(kol[s]))
                            .multiply(d[i - s][j - 1]));
        System.out.println(d[n][k].toString());
    }
}