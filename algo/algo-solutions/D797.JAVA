import java.math.BigInteger;
import java.util.Scanner;

class Solution {
    private static BigInteger C(int n, int k) {
        BigInteger res = BigInteger.ONE;
        for (int i = 1; i <= k; i++)
            res = res.multiply(BigInteger.valueOf(n - k + i)).divide(
                    BigInteger.valueOf(i));
        return res;
    }

    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(System.in);
        int p = in.nextInt(), q = in.nextInt(), k = in.nextInt();
        System.out.println((C(p, k).multiply(C(q, k))).toString());
    }
}