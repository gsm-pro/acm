import java.io.*;
import java.util.Scanner;

class Solution {
    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("input.txt"));
        try (PrintWriter out = new PrintWriter("output.txt")) {
            out.print(in.nextBigInteger().add(in.nextBigInteger()).pow(in.nextInt()));
        }
    }
}