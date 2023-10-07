import java.io.*;
import java.util.*;
import java.math.*;

public class Solution {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(
                new FileInputStream("input.txt")));
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter(
                new FileOutputStream("output.txt")));
        String s = in.readLine();
        String ws[] = s.split("\\s");
        int n = Integer.parseInt(ws[0]);
        int k = Integer.parseInt(ws[1]);
        BigInteger b[] = new BigInteger[n];
        for (int i = 0; i < n; i++) {
            s = in.readLine();
            String t = "";
            boolean z = true;
            for (int j = 0; j < s.length(); j++) {
                char c = s.charAt(j);
                if (c == '-' && z) {
                    t += c;
                    z = false;
                }
                if (Character.isDigit(c)) {
                    t += c;
                    z = false;
                }
            }
            BigInteger bb = new BigInteger(t);
            b[i] = bb;
        }
        Arrays.sort(b);
        BigInteger ans = BigInteger.ZERO;
        for (int i = 0; i < k; i++)
            ans = ans.add(b[i]);
        out.write(ans.toString());
        out.close();
    }
}