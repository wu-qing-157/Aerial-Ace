import java.io.*;
import java.util.*;

public class InputOptimize {
    private static BufferedReader reader;
    private static StringTokenizer tokenizer;
    private static String next() {
        try {
            while (tokenizer == null || !tokenizer.hasMoreTokens())
                tokenizer = new StringTokenizer(reader.readLine());
        } catch (IOException e) {
            // do nothing
        }
        return tokenizer.nextToken();
    }
    private static int nextInt() {
        return Integer.parseInt(next());
    }
    public static void main(String[] args) {
        reader = new BufferedReader(new InputStreamReader(System.in));
    }
}
