import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Solution {
    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(System.in);
        int N = in.nextInt();
        int[] M = new int[N];
        for (int i = 0; i < N; i++) {
            String line = in.next();
            for (int j = 0; j < N; j++) {
                if (line.charAt(j) == 'Y') {
                    M[i] |= (1 << j);
                }
            }
        }
        List<Integer> goodMasks = new ArrayList<>();
        boolean[] flag = new boolean[1 << N];
        for (int i = 0; i < (1 << N); i++) {
            int j;
            for (j = 0; j < N; j++) {
                if (((i >> j) & 1) != 0) {
                    if (flag[i - (1 << j)]) {
                        break;
                    }
                }
            }
            if (j < N) {
                flag[i] = true;
                continue;
            }
            int cur = 0;
            for (j = 0; j < N; j++) {
                if (((i >> j) & 1) != 0) {
                    cur |= (1 << j);
                    cur |= M[j];
                }
            }
            if (cur == (1 << N) - 1) {
                flag[i] = true;
                goodMasks.add(i);
            }
        }
        int[] D = new int[1 << (N + 1)];
        int ans = 0;
        for (int i = 0; i < (1 << N); i++) {
            for (Integer mask : goodMasks) {
                if ((i & mask) == 0) {
                    D[i + mask] = Math.max(D[i + mask], D[i] + 1);
                }
            }
            ans = Math.max(ans, D[i]);
        }
        System.out.print(ans);
    }
}