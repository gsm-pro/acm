import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.math.BigInteger;

public class Solution {
    public static int k;
    public static BigInteger r = BigInteger.ZERO;
    static BufferedReader in = new BufferedReader(new InputStreamReader(
            System.in));

    public static void Conv() throws IOException {
        String s = null;
        s = in.readLine();
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
        String op = null;
        String s;
        s = in.readLine();
        k = Integer.parseInt(s);
        Conv();
        BigInteger res = r;
        while (true) {
            op = in.readLine();
            if (op.equals("=")) {
                System.out.print(res);
                break;
            }
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