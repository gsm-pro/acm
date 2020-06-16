import java.math.BigInteger;

public class Solution {
    private static BigInteger f(int n) {
        return n < 2 ? BigInteger.ONE :
                java.util.stream.IntStream.rangeClosed(2, n)
                        .mapToObj(BigInteger::valueOf)
                        .reduce(BigInteger::multiply)
                        .get();
    }

    public static void main(String[] args) {
        int n = new java.util.Scanner(System.in).nextInt();
        System.out.print(f(3 * n - 3).divide(f(n - 1).pow(3)));
    }
}