import java.util.*;
import java.math.*;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        while (true) {
            int n = scanner.nextInt();
            if (n == 0) break;
            BigInteger a = BigInteger.ONE.shiftLeft(n).subtract(BigInteger.ONE);
            if (a.isProbablePrime(1000)) System.out.println(n + ":Prime");
            else System.out.println(n + ":NotPrime");
        }
    }
}
