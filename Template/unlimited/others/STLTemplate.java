import java.util.*;

public class STLTemplate {
    private static void stl() {
        List<Integer> list = new ArrayList<>();
        List[] lists = new List[100]; lists[0] = new ArrayList<Integer>();
        list.remove(list.get(1)); list.remove(list.size() - 1); list.clear();
        Queue<Integer> queue = new LinkedList<>();
        Queue<Integer> priorityQueue = new PriorityQueue<>();
        queue.peek(); queue.poll();
        Deque<Integer> deque = new ArrayDeque<>();
        deque.peekFirst(); deque.peekLast(); deque.pollFirst();
        TreeSet<Integer> set = new TreeSet<>();
        TreeSet<Integer> anotherSet = new TreeSet<>(Comparator.reverseOrder());
        set.ceiling(1); set.floor(1); set.lower(1); set.higher(1); set.contains(1);
        HashSet<Integer> hashSet = new HashSet<>();
        HashMap<String, Integer> map = new HashMap<>();
        TreeMap<String, Integer> treeMap = new TreeMap<>();
        map.put("", 1); map.get("");
        map.forEach((string, integer) -> System.out.println(string + integer));
        Arrays.sort(new int[10]);
        Arrays.sort(new Integer[10], (a, b) -> b.compareTo(a));
        Arrays.sort(new Integer[10], Comparator.comparingInt((a) -> (int) a).reversed());
        long a = 1_000_000_000_000_000_000L;
        int b = Integer.MAX_VALUE;
        int c = 'a';
    }
}
