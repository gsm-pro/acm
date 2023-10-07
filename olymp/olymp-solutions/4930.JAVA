import java.io.PrintWriter;
import java.nio.file.*;

public class Solution {
    public static void main(String... args) throws Exception {
        StringBuilder timeLine = new StringBuilder();
        for (int year = 2000; year <= 2020; year++)
            for (int month = 1; month <= 12; month++)
                timeLine.append(java.time.YearMonth.of(year, month).lengthOfMonth());
        try (PrintWriter out = new PrintWriter("output.txt")) {
            out.write(timeLine.indexOf(Files.readAllLines(Paths.get("input.txt")).get(1)
                    .replace(" ", "")) >= 0 ? "Yes" : "No");
        }
    }
}