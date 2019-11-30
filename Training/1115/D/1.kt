import java.util.*

fun main() {
    val cases = readLine()!!.toInt()
    for (cas in 1..cases) {
        var s = readLine()!!
        s = s.replace(Regex("a$"), "as")
        s = s.replace(Regex("[iy]$"), "ios")
        s = s.replace(Regex("l$"), "les")
        s = s.replace(Regex("ne?$"), "anes")
        s = s.replace(Regex("o$"), "os")
        s = s.replace(Regex("r$"), "res")
        s = s.replace(Regex("t$"), "tas")
        s = s.replace(Regex("u$"), "us")
        s = s.replace(Regex("v$"), "ves")
        s = s.replace(Regex("w$"), "was")
        println(s)
    }
}
