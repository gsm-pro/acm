import java.math.BigInteger;
import java.util.Scanner;

public class Solution {
    public static boolean isPrime(long n) {
        return BigInteger.valueOf(n).isProbablePrime(5);
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        long d = 5, p = 0, n = in.nextLong();
        boolean p2 = true;
        while (n % 2 == 0) {
            n /= 2;
            p++;
        }
        if (p > 0) {
            System.out.println(2 + " " + p);
        }
        p = 0;
        while (n % 3 == 0) {
            n /= 3;
            p++;
        }
        if (p > 0) {
            System.out.println(3 + " " + p);
        }
        p = 0;
        while (!isPrime(n) && n != 1) {
            while (n % d != 0) {
                d += (p2 ? 2 : 4);
                p2 = !p2;
            }
            while (n % d == 0) {
                p++;
                n = n / d;
            }
            System.out.println(d + " " + p);
            p = 0;
        }
        if (n > 1) {
            System.out.println(n + " 1");
        }
    }
}