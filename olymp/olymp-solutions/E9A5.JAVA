import java.util.*;
import java.io.*;
import java.math.*;

public class Solution {
    public static void main(String[] args) throws Exception {
        int a[] = new int[101];
        BufferedReader in = new BufferedReader(new InputStreamReader(new FileInputStream("input.txt")));
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter(new FileOutputStream("output.txt")));
        int n = Integer.parseInt(in.readLine());
        StringTokenizer st = new StringTokenizer(in.readLine());
        for (int i = 0; i < n; i++)
            a[i] = Integer.parseInt(st.nextToken());
        BigInteger ans = BigInteger.ONE;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                ans = ans.multiply(BigInteger.valueOf(a[j] - a[i]));
        out.write(ans.toString());
        out.close();
    }
}