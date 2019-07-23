import java.util.*;
import java.math.*;
import java.io.*;

public class E {
    private static long c(int n, int m) {
        long ans = 1L;
        for (int i = 1, j = n; i <= m; ) {
            ans *= j;
            ans /= i;
            i++; j--;
        }
        return ans;
    }
    public static void main(String[] args) throws Exception {
        Scanner scanner = new Scanner(new FileReader("permutominoes.in"));
        int n = scanner.nextInt();
        n -= 2;
        BigInteger ans = BigInteger.ZERO;
        for (int a = 0; a <= n; a++)
            for (int b = 0; a + b <= n; b++)
                for (int c = 0; a + b + c <= n; c++) {
                    int d = n - a - b - c;
                    ans = ans.add(BigInteger.valueOf(c(n, a + b) * c(n, a + d)));
                }
        FileWriter writer = new FileWriter("permutominoes.out");
        writer.write(ans + "\n");
        writer.close();
    }
}
