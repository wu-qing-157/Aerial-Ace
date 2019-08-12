import java.math.*

val set = HashSet<BigInteger>()

fun solve(a: BigInteger, cur: BigInteger, last: Int) {
    if (last == 1 && a != BigInteger.ONE) {
        if (set.all { a % set != BigInteger.ZERO })
            set.add(a)
    }
    solve(a + cur, cur * 10, 1)
    solve(a, cur * 10, 0)
}

fun main() {
    solve(BigInteger.ZERO, BigInteger.ONE, 0)
    return
}
