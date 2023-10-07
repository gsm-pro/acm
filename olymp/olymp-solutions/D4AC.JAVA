import java.io.*;
import java.math.BigInteger;

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(
                new FileInputStream("input.txt")));
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter(
                new FileOutputStream("output.txt")));
        BigInteger[] z = new BigInteger[1005];
        z[1] = BigInteger.ONE;
        z[2] = BigInteger.valueOf(2);
        for (int i = 3; i <= 1003; i++)
            z[i] = z[i - 1].add(z[i - 2]);
        String a = in.readLine();
        BigInteger cc = BigInteger.ZERO;
        for (int i = 0; i < a.length(); i++)
            if (a.charAt(i) == '1')
                cc = cc.add(z[a.length() - i]);
        a = in.readLine();
        for (int i = 0; i < a.length(); i++)
            if (a.charAt(i) == '1')
                cc = cc.add(z[a.length() - i]);
        if (BigInteger.ZERO.equals(cc))
            out.write("0");
        else {
            StringBuilder c = new StringBuilder();
            int q = 0;
            for (int i = 1002; i >= 1; i--) {
                if (q == 0 && cc.compareTo(z[i]) >= 0) {
                    c.append("1");
                    cc = cc.subtract(z[i]);
                    q = 1;
                } else {
                    c.append("0");
                    q = 0;
                }
            }
            int i = 0;
            while (c.charAt(i) == '0')
                i++;
            out.write(c.substring(i));
        }
        out.close();
    }
}