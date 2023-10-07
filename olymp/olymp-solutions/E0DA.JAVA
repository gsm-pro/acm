import java.util.*;
import java.io.*;

public class Solution {
    public static void main(String[] args) throws Exception {
        int x[] = new int[25001];
        int a[] = new int[25000];
        Scanner in = new Scanner(new File("input.txt"));
        PrintWriter out = new PrintWriter("output.txt");
        int n = in.nextInt();
        int ans = 0;
        for (int i = 0; i <= n - 2; i++)
            x[i] = in.nextInt();
        if (n == 2)
            ans = x[0];
        else {
            ans = x[0] + x[n - 2];
            if (n == 3)
                ans += x[2];
            n -= 3;
            if (n > 0) {
                a[1] = x[1];
                a[2] = x[2];
                for (int i = 3; i <= n; i++)
                    a[i] = Math.min(a[i - 2], a[i - 1]) + x[i];
                ans += Math.min(a[n], a[n - 1]);
            }
        }
        out.println(ans);
        out.close();
    }
}