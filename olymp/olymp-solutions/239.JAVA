import java.io.*;
import java.math.*;

public class Solution {
    public static int k;
    public static BigInteger r = BigInteger.ZERO;
    static String s;

    public static void Conv() {
        r = BigInteger.ZERO;
        long step = 1, f, z;
        int i, m;
        char q;
        for (i = s.length() - 1; i >= 0; i--) {
            q = s.charAt(i);
            m = (int) q;
            if (m < 60)
                f = m - 48;
            else
                f = m - 55;
            z = f * step;
            r = r.add(BigInteger.valueOf(z));
            step *= k;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(
                new FileInputStream("input.txt")));
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter(
                new FileOutputStream("output.txt")));
        String op = null;
        s = in.readLine();
        k = Integer.parseInt(s);
        s = in.readLine();
        Conv();
        BigInteger res = r;
        while (true) {
            op = in.readLine();
            if (op.equals("=")) {
                out.write(res.toString());
                out.close();
                break;
            }
            s = in.readLine();
            Conv();
            if (op.equals("+"))
                res = res.add(r);
            if (op.equals("-"))
                res = res.subtract(r);
            if (op.equals("*"))
                res = res.multiply(r);
        }
    }
}