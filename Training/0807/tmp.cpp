#include <bits/stdc++.h>
 
using namespace std;
 
const int inf = 0x3f3f3f3f;
 
namespace flow {
struct edge_t {
  int to, cap, rev;
 
  edge_t(int t, int c, int r) {
    to = t;
    cap = c;
    rev = r;
  }
};
 
int n, source, sink, answer;
vector<vector<edge_t>> adj;
vector<int> dist, current;
 
void init(int v, int s, int t) {
  n = v;
  source = s;
  sink = t;
  answer = 0;
  adj.clear();
  adj.resize(n);
  dist.resize(n);
  current.resize(n);
}
 
void add(int x, int y, int c) {
  adj[x].push_back(edge_t(y, c, adj[y].size()));
  adj[y].push_back(edge_t(x, 0, adj[x].size() - 1));
}
 
bool bfs() {
  queue<int> q;
  for (int i = 0; i < n; ++i) {
    dist[i] = -1;
  }
  dist[source] = 0, q.push(source);
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    for (auto e : adj[x]) {
      if (e.cap && !~dist[e.to]) {
        dist[e.to] = dist[x] + 1;
        if (e.to == sink) {
          return true;
        }
        q.push(e.to);
      }
    }
  }
  return false;
}
 
int dfs(int x, int f) {
  if (x == sink) {
    return f;
  }
  for (int &i = current[x]; ~i; --i) {
    edge_t &e = adj[x][i];
    if (e.cap && dist[e.to] == dist[x] + 1) {
      int w = dfs(e.to, min(e.cap, f));
      if (w) {
        e.cap -= w;
        adj[e.to][e.rev].cap += w;
        return w;
      }
    }
  }
  return 0;
}
 
int max_flow() {
  while (bfs()) {
    for (int i = 0; i < n; ++i) {
      current[i] = adj[i].size() - 1;
    }
    while (true) {
      int flow = dfs(source, inf);
      if (!flow) {
        break;
      }
      answer += flow;
    }
  }
  return answer;
}
}
 
using flow::source;
using flow::sink;
using flow::init;
using flow::add;
using flow::max_flow;
 
int main() {
#ifdef wxh010910
  freopen("input.txt", "r", stdin);
#endif
  int n, m;
  cin >> n >> m;
  vector<string> board(n);
  for (int i = 0; i < n; ++i) {
    cin >> board[i];
  }
  init(n * m + 2, n * m, n * m + 1);
  vector<int> dx = {1, -1, 0, 0};
  vector<int> dy = {0, 0, 1, -1};
  int left = 0, right = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (i + j & 1) {
        for (int d = 0; d < 4; ++d) {
          int x = i + dx[d], y = j + dy[d];
          if (x >= 0 && x < n && y >= 0 && y < m) {
            add(i * m + j, x * m + y, 2);
          }
        }
        add(source, i * m + j, 1 + (board[i][j] == '-'));
        left += 1 + (board[i][j] == '-');
      } else {
        add(i * m + j, sink, 1 + (board[i][j] == '-'));
        right += 1 + (board[i][j] == '-');
      }
    }
  }
  puts(max_flow() == max(left, right) ? "Y" : "N");
  return 0;
}
