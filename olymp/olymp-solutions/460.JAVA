import java.math.*;
import java.util.*;
import java.io.*;

class Solution {
    public static void main(String[] args) throws Exception {
        try (PrintWriter w = new PrintWriter(new File("output.txt"))) {
            Scanner s = new Scanner(new File("input.txt"));
            w.print(BigInteger.ONE.shiftLeft(s.nextInt()).
                    add(BigInteger.ONE.shiftLeft(s.nextInt())).subtract(BigInteger.valueOf(2L)));
        }
    }
}