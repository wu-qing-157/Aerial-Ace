import java.math.*
import java.util.*

fun main() {
    val ps = mutableListOf<Int>()
    var cur = BigInteger.ONE
    val up = BigInteger.TEN.pow(100)

    out@for (i in 2..100000) {
        if (cur > up) break
        for (j in ps) if (i % j == 0) continue@out
        ps += i
        cur *= BigInteger.valueOf(i.toLong())
    }

    val scanner = Scanner(System.`in`)

    for (cas in 0 until scanner.nextInt()) {
        val n = scanner.nextBigInteger()
        var p = BigInteger.ONE
        var q = BigInteger.ONE
        for (i in ps) {
            if (q * BigInteger.valueOf(i.toLong()) > n) break
            p *= BigInteger.valueOf(i.toLong())
            q *= BigInteger.valueOf((i + 1).toLong())
        }
        val gcd = p.gcd(q)
        p /= gcd
        q /= gcd
        println("$p/$q")
    }
}
