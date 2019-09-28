import java.util.*
import java.math.*
import java.io.*

fun dfs(l: Int, r: Int, ls: HashSet<Int>, rs: HashSet<Int>, ret: HashMap<Pair<Int, Int>, Int>) {
    if (l == r - 1) {
        val query = Pair(if (ls.contains(l)) ls.size - 1 else ls.size, rs.size)
        ret[query] = (ret[query] ?: 0) + 1
        return
    }
    val m = (l + r) / 2
    if (ls.contains(m)) {
        dfs(m, r, ls, rs, ret)
    } else {
        ls.add(m)
        dfs(m, r, ls, rs, ret)
        ls.remove(m)
    }
    if (rs.contains(m)) {
        dfs(l, m, ls, rs, ret)
    } else {
        rs.add(m)
        dfs(l, m, ls, rs, ret)
        rs.remove(m)
    }
}

fun main() {
    val n = Scanner(FileReader("binary.in")).nextInt()
    var ans = BigInteger.ZERO
    val ls = HashSet<Int>()
    val rs = HashSet<Int>()
    val ret = HashMap<Pair<Int, Int>, Int>()

    dfs(0, n, ls, rs, ret)
    for ((query, times) in ret) {
        var cans = BigInteger.ZERO
        for (x in 1..n)
            cans += BigInteger.valueOf(x + 0L).pow(query.first) * BigInteger.valueOf(n - x + 0L).pow(query.second);
        ans += cans * BigInteger.valueOf(n + 0L).pow(n - 1 - query.first - query.second) * BigInteger.valueOf(times + 0L)
    }

    val writer = FileWriter("binary.out")
    writer.write("$ans\n")
    writer.close()
}
