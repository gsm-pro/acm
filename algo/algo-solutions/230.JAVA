import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class Solution {
    public static void main(String[] args) throws Exception {
        new Solution().run();
    }

    private void run() throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter(System.out));
        int n = Integer.parseInt(in.readLine());
        final ExecutorService service = Executors.newFixedThreadPool(2);
        final int[] number = new int[n];
        List<Integer> index = new ArrayList<>();
        List<Future<Integer>> result = new ArrayList<>();
        String tmp;
        int cur = 0;
        while ((tmp = in.readLine()) != null) {
            String[] t = tmp.split(" ");
            for (String a : t) {
                if (!a.isEmpty()) {
                    index.add(cur);
                    number[cur++] = Integer.parseInt(a);
                }
            }
        }
        in.close();
        for (final Integer z : index) {
            result.add(service.submit(() -> {
                int c = 0, i, num = number[z];
                for (i = 2; i * i < num; i++) {
                    if (num % i == 0) {
                        c++;
                    }
                }
                return (c << 1) + (i * i == num ? 1 : 0) + (num > 1 ? 1 : 0) + 1;
            }));
        }
        service.shutdown();
        for (Future<Integer> f : result) {
            out.write(f.get() + "\n");
        }
        out.close();
    }
}