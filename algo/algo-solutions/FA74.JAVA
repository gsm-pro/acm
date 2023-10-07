import java.io.*;
import java.util.*;
import java.math.*;

public class Solution {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        PrintWriter out = new PrintWriter(System.out);
        while (in.hasNextBigInteger()) {
            BigInteger a = in.nextBigInteger();
            String op = in.next();
            BigInteger b = in.nextBigInteger();
            if (op.equals("+")) System.out.println(a.add(b));
            if (op.equals("-")) System.out.println(a.subtract(b));
            if (op.equals("*")) System.out.println(a.multiply(b));
        }
        in.close();
        out.close();
    }
}