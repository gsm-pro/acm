import java.math.*;
import java.util.*;

class Fraction {
    BigInteger num, den;
}

public class Solution {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int N = in.nextInt();
        int n = 1 << (2 * N + 1);
        Fraction x[] = new Fraction[4000];
        Fraction y[] = new Fraction[4000];
        for (int i = 0; i < 4000; i++) {
            x[i] = new Fraction();
            y[i] = new Fraction();
        }
        int l = 0, r = -1;
        for (int i = 0; i < n; i++) {
            r++;
            x[i].num = in.nextBigInteger();
            x[i].den = BigInteger.ONE;
            y[i].num = in.nextBigInteger();
            y[i].den = BigInteger.ONE;
        }
        while (true) {
            Fraction ax1 = x[l];
            Fraction ay1 = y[l];
            l++;
            Fraction bx1 = x[l];
            Fraction by1 = y[l];
            l++;
            Fraction aa1 = new Fraction();
            aa1.num = ((by1.num).multiply(ay1.den)).subtract((by1.den)
                    .multiply(ay1.num));
            aa1.den = (ay1.den).multiply(by1.den);
            Fraction bb1 = new Fraction();
            bb1.num = ((ax1.num).multiply(bx1.den)).subtract((ax1.den)
                    .multiply(bx1.num));
            bb1.den = (bx1.den).multiply(ax1.den);
            Fraction AyBx = new Fraction();
            AyBx.num = (ay1.num).multiply(bx1.num);
            AyBx.den = (ay1.den).multiply(bx1.den);
            Fraction AxBy = new Fraction();
            AxBy.num = (ax1.num).multiply(by1.num);
            AxBy.den = (ax1.den).multiply(by1.den);
            Fraction cc1 = new Fraction();
            cc1.num = ((AyBx.num).multiply(AxBy.den)).subtract((AyBx.den)
                    .multiply(AxBy.num));
            cc1.den = (AyBx.den).multiply(AxBy.den);
            BigInteger A1 = (aa1.num).multiply(bb1.den).multiply(cc1.den);
            BigInteger B1 = (bb1.num).multiply(aa1.den).multiply(cc1.den);
            BigInteger C1 = (cc1.num).multiply(aa1.den).multiply(bb1.den);
            if (A1.compareTo(BigInteger.ZERO) == 0
                    && B1.compareTo(BigInteger.ZERO) == 0) {
                System.out.println("I can't draw that");
                return;
            }
            BigInteger gcd = (A1).gcd(B1).gcd(C1);
            A1 = A1.divide(gcd);
            B1 = B1.divide(gcd);
            C1 = C1.divide(gcd);
            if (l - r == 1) {
                String z = A1.toString() + " " + B1.toString() + " "
                        + C1.toString();
                System.out.println(z);
                break;
            }
            Fraction ax2 = x[l];
            Fraction ay2 = y[l];
            l++;
            Fraction bx2 = x[l];
            Fraction by2 = y[l];
            l++;
            Fraction aa2 = new Fraction();
            aa2.num = ((by2.num).multiply(ay2.den)).subtract((by2.den)
                    .multiply(ay2.num));
            aa2.den = (ay2.den).multiply(by2.den);
            Fraction bb2 = new Fraction();
            bb2.num = ((ax2.num).multiply(bx2.den)).subtract((ax2.den)
                    .multiply(bx2.num));
            bb2.den = (bx2.den).multiply(ax2.den);
            AyBx.num = (ay2.num).multiply(bx2.num);
            AyBx.den = (ay2.den).multiply(bx2.den);
            AxBy.num = (ax2.num).multiply(by2.num);
            AxBy.den = (ax2.den).multiply(by2.den);
            Fraction cc2 = new Fraction();
            cc2.num = ((AyBx.num).multiply(AxBy.den)).subtract((AyBx.den)
                    .multiply(AxBy.num));
            cc2.den = (AyBx.den).multiply(AxBy.den);
            BigInteger A2 = (aa2.num).multiply(bb2.den).multiply(cc2.den);
            BigInteger B2 = (bb2.num).multiply(aa2.den).multiply(cc2.den);
            BigInteger C2 = (cc2.num).multiply(aa2.den).multiply(bb2.den);
            if (A2.compareTo(BigInteger.ZERO) == 0
                    && B2.compareTo(BigInteger.ZERO) == 0) {
                System.out.println("I can't draw that");
                return;
            }
            gcd = (A2).gcd(B2).gcd(C2);
            A2 = A2.divide(gcd);
            B2 = B2.divide(gcd);
            C2 = C2.divide(gcd);
            if ((A1.multiply(B2)).subtract(A2.multiply(B1)).compareTo(
                    BigInteger.ZERO) == 0) {
                System.out.println("I can't draw that");
                return;
            }
            Fraction xxx = new Fraction();
            Fraction yyy = new Fraction();
            xxx.num = (B1.multiply(C2)).subtract(B2.multiply(C1));
            xxx.den = (A1.multiply(B2)).subtract(A2.multiply(B1));
            yyy.num = (C1.multiply(A2)).subtract(C2.multiply(A1));
            yyy.den = (A1.multiply(B2)).subtract(A2.multiply(B1));
            r++;
            x[r] = xxx;
            y[r] = yyy;
        }
    }
}