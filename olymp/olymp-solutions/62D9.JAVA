import java.io.*;
import java.util.*;
import java.util.stream.*;

public class Solution {
    public static void main(String... args) throws Exception {
        Scanner in = new Scanner(new File("input.txt"));
        int n = in.nextInt(), t = in.nextInt();
        List<Long> x = IntStream.range(0, n).mapToObj(i -> in.nextLong()).collect(Collectors.toList());
        long cycles = t / n, rem = t % n, sum = x.stream().reduce(0L, Long::sum);
        List<Long> ans = IntStream.range(0, n).mapToObj(i -> sum * cycles).collect(Collectors.toList());
        for (int i = 1; i <= rem; i++) {
            for (int j = 0; j < n; j++) ans.set(j, ans.get(j) + x.get(j));
            x.add(x.remove(0));
        }
        try (PrintWriter out = new PrintWriter("output.txt")) {
            out.print(ans.toString()
                    .replaceAll(",", "")
                    .replaceAll("\\[", "")
                    .replaceAll("]", ""));
        }
    }
}