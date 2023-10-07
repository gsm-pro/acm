import java.io.*;
import java.util.*;
import java.util.stream.IntStream;

public class Solution {
    List<Integer>[] G = new List[200001];
    int N, M, maxDst, maxDstV;
    int[] dst = new int[200001];
    java.util.function.Consumer<Integer> dfs, dfsRunner;

    {
        dfs = o -> {
            for (int v : G[o]) {
                if (dst[v] == -1) {
                    dst[v] = dst[o] + 1;
                    if (dst[v] > maxDst) {
                        maxDst = dst[v];
                        maxDstV = v;
                    }
                    dfs.accept(v);
                }
            }
        };

        dfsRunner = o -> {
            Arrays.fill(dst, 0, N, -1);
            dst[o] = maxDst = 0;
            dfs.accept(o);
        };
    }

    public static void main(String[] args) throws Exception {
        new Solution().run();
    }

    void run() throws Exception {
        try (Scanner in = new Scanner(new File("input.txt"))) {
            N = in.nextInt();
            M = in.nextInt();
            IntStream.range(0, N).forEach(i -> G[i] = new ArrayList<>());
            IntStream.range(1, N).forEach(i -> {
                int v = in.nextInt() - 1;
                G[i].add(v);
                G[v].add(i);
            });
        }
        dfsRunner.accept(0);
        long height = maxDst + 1;
        dfsRunner.accept(maxDstV);
        long diameter = maxDst + 1;
        try (PrintWriter out = new PrintWriter("output.txt")) {
            out.print(maxDstV == 0 ? diameter * M : diameter + 2 * (M - 1) * height);
        }
    }
}