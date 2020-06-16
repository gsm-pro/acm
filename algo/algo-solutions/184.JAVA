import java.util.*;
import java.io.*;
import java.math.*;

public class Solution {
    public static BigInteger[][] z;
    
    public static void main(String[] argv) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(st.nextToken());
        int m = Integer.parseInt(st.nextToken());
        z = new BigInteger[2][m + 1];
        for (int i = 0; i < 2; i++)
            for (int j = 0; j <= m; j++)
                z[i & 1][j] = BigInteger.ZERO;
        String a;
        for (int i = 1; i <= n; i++) {
            st = new StringTokenizer(in.readLine());
            a = st.nextToken();
            for (int j = 1; j <= m; j++) z[i & 1][j] = BigInteger.ZERO;
            for (int j = 1; j <= m; j++) {
                if (i == 1 && j == 1)
                    z[i][j] = BigInteger.ONE;
                else if (a.charAt(j - 1) != '*')
                    z[i & 1][j] = z[(i - 1) & 1][j].add(z[i & 1][j - 1]);
            }
        }
        System.out.println(z[n & 1][m]);
    }
}