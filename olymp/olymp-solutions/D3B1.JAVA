import java.io.PrintWriter;
import java.nio.file.*;
import java.util.*;

public class Solution {
    public static void main(String... args) throws Exception {
        Set<Character> vowels = new LinkedHashSet<>(Arrays.asList('A', 'a', 'E', 'e', 'I', 'i', 'O', 'o', 'U', 'u'));
        Set<Character> consonants = new LinkedHashSet<>();
        for (Character c : "abcdefghijklmnopqrstuvwxyz".toCharArray()) {
            Character C = Character.toUpperCase(c);
            if (!vowels.contains(C)) consonants.add(C);
            if (!vowels.contains(c)) consonants.add(c);
        }
        try (PrintWriter out = new PrintWriter("output.txt")) {
            List<Character> chars = Files.readAllLines(Paths.get("input.txt")).get(0)
                    .chars().mapToObj(c -> (char) c).collect(java.util.stream.Collectors.toList());
            int len = chars.size(), ans = 0;
            int cr1 = 2 - Boolean.compare(chars.stream().anyMatch(c -> c >= 'A' && c <= 'Z'), false)
                    - Boolean.compare(chars.stream().anyMatch(c -> c >= 'a' && c <= 'z'), false);
            int cr2 = 2 - Boolean.compare(chars.stream().anyMatch(vowels::contains), false)
                    - Boolean.compare(chars.stream().anyMatch(consonants::contains), false);
            if (chars.stream().noneMatch(c -> c >= '0' && c <= '9')) {
                ans++;
                len++;
            }
            if (cr1 + cr2 > 0) {
                int cr = Math.max(cr1, cr2);
                ans += cr;
                len += cr;
            }
            if (len < 8) ans += (8 - len);
            out.print(ans);
        }
    }
}