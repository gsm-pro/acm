import java.io.*;
import java.util.*;
import java.math.*;

public class Solution {
    public static void main (String[] args)
    {
        Scanner in = new Scanner(System.in);
        PrintWriter out = new PrintWriter(System.out);
        BigInteger a = in.nextBigInteger();
        BigInteger b = in.nextBigInteger();
        BigInteger c = a.divide(b);
        BigInteger r = a.subtract(b.multiply(c));
        System.out.println(c);
        System.out.println(r);
        in.close(); 
        out.close();
    }
}