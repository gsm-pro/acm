import java.io.*;
import java.util.*;
import java.math.*;

public class Solution {
    public static void main(String[] X) throws Exception {
        Scanner in = new Scanner(new File("input.txt"));
        PrintWriter out = new PrintWriter(new File("output.txt"));
        int a[] = new int[5001];
        BigInteger z[] = new BigInteger[5001];
        int n = in.nextInt();
        for (int i = 1; i <= n; i++)
            a[i] = in.nextInt();
        z[0] = BigInteger.ONE;
        for (int i = 1; i <= n; i++) {
            int j = i - 1;
            while (j > 0 && (a[j] + a[i]) % 2 != 0)
                j--;
            z[i] = z[i - 1].add(z[i - 1]);
            if (j != 0)
                z[i] = z[i].subtract(z[j - 1]);
        }
        out.print((z[n].subtract(BigInteger.ONE)).toString());
        out.close();
    }
}