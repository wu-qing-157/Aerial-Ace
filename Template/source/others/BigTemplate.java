import java.math.*;

public class BigTemplate {
    // BigInteger & BigDecimal
    private static void bigDecimal() {
        BigDecimal a = BigDecimal.valueOf(1.0);
        BigDecimal b = a.setScale(50, RoundingMode.HALF_EVEN);
        BigDecimal c = b.abs();
        // if scale omitted, b.scale is used
        BigDecimal d = c.divide(b, 50, RoundingMode.HALF_EVEN);
        // since Java 9
        BigDecimal e = d.sqrt(new MathContext(50, RoundingMode.HALF_EVEN));
        BigDecimal x = new BigDecimal(BigInteger.ZERO);
        BigInteger y = BigDecimal.ZERO.toBigInteger(); // RoundingMode.DOWN
        y = BigDecimal.ZERO.setScale(0, RoundingMode.HALF_EVEN).unscaledValue();
    }

    // sqrt for Java 8
    // can solve scale=100 for 10000 times in about 1 second
    private static BigDecimal sqrt(BigDecimal a, int scale) {
        if (a.compareTo(BigDecimal.ZERO) < 0)
            return BigDecimal.ZERO.setScale(scale, RoundingMode.HALF_EVEN);
        int length = a.precision() - a.scale();
        BigDecimal ret = new BigDecimal(BigInteger.ONE, -length / 2);
        for (int i = 1; i <= Integer.highestOneBit(scale) + 10; i++)
            ret = ret.add(a.divide(ret, scale, RoundingMode.HALF_EVEN)).divide(BigDecimal.valueOf(2), scale, RoundingMode.HALF_EVEN);
        return ret;
    }

    // can solve a=2^10000 for 100000 times in about 1 second
    private static BigInteger sqrt(BigInteger a) {
        int length = a.bitLength() - 1;
        BigInteger l = BigInteger.ZERO.setBit(length / 2), r = BigInteger.ZERO.setBit(length / 2);
        while (!l.equals(r)) {
            BigInteger m = l.add(r).shiftRight(1);
            if (m.multiply(m).compareTo(a) < 0)
                l = m.add(BigInteger.ONE);
            else
                r = m;
        }
        return l;
    }

    private static class BigFraction {
        private BigInteger a, b;

        BigFraction(BigInteger a, BigInteger b) {
            BigInteger gcd = a.gcd(b);
            this.a = a.divide(gcd);
            this.b = b.divide(gcd);
        }

        BigFraction add(BigFraction o) {
            BigInteger gcd = b.gcd(o.b);
            BigInteger tempProduct = b.divide(gcd).multiply(o.b.divide(gcd));
            BigInteger ansA = a.multiply(o.b.divide(gcd)).add(o.a.multiply(b.divide(gcd)));
            BigInteger gcd2 = ansA.gcd(gcd);
            ansA = ansA.divide(gcd2);
            gcd2 = gcd.divide(gcd2);
            return new BigFraction(ansA, gcd2.multiply(tempProduct));
        }

        BigFraction subtract(BigFraction o) {
            BigInteger gcd = b.gcd(o.b);
            BigInteger tempProduct = b.divide(gcd).multiply(o.b.divide(gcd));
            BigInteger ansA = a.multiply(o.b.divide(gcd)).subtract(o.a.multiply(b.divide(gcd)));
            BigInteger gcd2 = ansA.gcd(gcd);
            ansA = ansA.divide(gcd2);
            gcd = gcd.divide(gcd2);
            return new BigFraction(ansA, gcd2.multiply(tempProduct));
        }

        BigFraction multiply(BigFraction o) {
            BigInteger gcd1 = a.gcd(o.b);
            BigInteger gcd2 = b.gcd(o.a);
            return new BigFraction(a.divide(gcd1).multiply(o.a.divide(gcd2)), b.divide(gcd2).multiply(o.b.divide(gcd1)));
        }

        @Override
        public String toString() {
            return a + "/" + b;
        }
    }
}
