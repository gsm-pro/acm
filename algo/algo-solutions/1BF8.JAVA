import java.io.*;
import java.util.*;
import java.math.*;

public class Solution {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        PrintWriter out = new PrintWriter(System.out);
        int n = in.nextInt();
        BigInteger a = BigInteger.ONE;
        BigInteger b = BigInteger.ONE;
        BigInteger c = BigInteger.ZERO;
        for (int i = 3; i <= n; i++) {
            c = a.add(a);
            c = c.add(a);
            c = c.subtract(b);
            b = a;
            a = c;
        }
        if (n == 1) System.out.println("1");
        if (n == 2) System.out.println("1");
        if (n > 2) System.out.println(c);
        in.close();
        out.close();
    }
}