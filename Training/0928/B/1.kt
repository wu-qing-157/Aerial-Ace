import java.util.*
import java.math.*
import java.io.*

fun main() {
    val writer = FileWriter("table")
    for (n in 1..1000) {
        val jie = Array(n + 1) { BigInteger.ZERO }
        jie[0] = BigInteger.ONE
        for (i in 1..n) jie[i] = jie[i - 1] * BigInteger.valueOf(i.toLong())
        fun p(n: Int, m: Int) = if (m < 0 || m > n) BigInteger.ZERO else jie[n] / jie[n - m]
        
        var ans = BigInteger.ZERO
        val ls = HashSet<Int>()
        val rs = HashSet<Int>()
        fun dfs(l: Int, r: Int) {
            if (l == r - 1) {
                val ll = if (ls.contains(l)) ls.size - 1 else ls.size
                val rr = rs.size
                for (x in 1..n)
                    ans += BigInteger.valueOf(x + 0L).pow(ll) * BigInteger.valueOf(n - x + 0L).pow(rr) * BigInteger.valueOf(n + 0L).pow(n - 1 - ll - rr)
                return
            }
            val m = (l + r) / 2
            if (ls.contains(m)) {
                dfs(m, r)
            } else {
                ls.add(m)
                dfs(m, r)
                ls.remove(m)
            }
            if (rs.contains(m)) {
                dfs(l, m)
            } else {
                rs.add(m)
                dfs(l, m)
                rs.remove(m)
            }
        }

        dfs(0, n)

        println("f[$n] = $ans;")
        writer.write("f[$n] = $ans;\n")
    }
}
