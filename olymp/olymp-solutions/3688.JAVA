import java.io.*;
import java.util.*;

class Solution {
    public static void main(String[] args) throws Exception {
        StringBuilder a = new StringBuilder();
        StringBuilder b = new StringBuilder(" ");
        java.util.stream.IntStream.rangeClosed(1, 177).forEachOrdered(i -> b.append(a.append(i)));
        try (Scanner sc = new Scanner(new File("input.txt"))) {
            try (PrintWriter pw = new PrintWriter(new File("output.txt"))) {
                pw.write(b.charAt(sc.nextInt()));
            }
        }
    }
}