import java.io.*;
import java.math.*;

public class Solution {
    static BigInteger[] F = new BigInteger[201];
    static BigInteger[] GRAF = new BigInteger[201];
    static BigInteger[][] CNK = new BigInteger[201][201];

    static public BigInteger G(int n) {
        return BigInteger.valueOf(2).pow(n * (n - 1) / 2);
    }

    static public BigInteger C(int n, int k) {
        return (F[n].divide(F[k])).divide(F[n - k]);
    }

    public static void main(String[] args) throws Exception {
        PrintWriter out = new PrintWriter(new File("output.txt"));
        F[0] = BigInteger.ONE;
        F[1] = BigInteger.ONE;
        for (int i = 2; i <= 200; i++)
            F[i] = F[i - 1].multiply(BigInteger.valueOf(i));
        for (int i = 1; i <= 200; i++)
            GRAF[i] = G(i);
        for (int i = 1; i <= 200; i++)
            for (int j = i; j <= 200; j++)
                CNK[i][j] = C(j, i);
        BigInteger[] kol = new BigInteger[201];
        int n = 200;
        kol[1] = BigInteger.ONE;
        for (int i = 2; i <= n; i++) {
            BigInteger sum = BigInteger.ZERO;
            for (int k = 1; k <= i - 1; k++)
                sum = sum.add((BigInteger.valueOf(k).multiply(CNK[k][i]))
                        .multiply(kol[k].multiply(GRAF[i - k])));
            kol[i] = GRAF[i].subtract(sum.divide(BigInteger.valueOf(i)));
        }
        out.println(kol[n].toString());
        out.close();
    }
}