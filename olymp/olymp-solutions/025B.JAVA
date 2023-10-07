import java.io.*;
import java.math.*;
import java.util.*;

public class Solution {
    public static void main(String[] args) throws Exception {
        PrintWriter out = new PrintWriter("output.txt");
        out.print(BigInteger.ONE.shiftLeft(new Scanner(new File("input.txt")).nextInt()).subtract(BigInteger.ONE));
        out.close();
    }
}