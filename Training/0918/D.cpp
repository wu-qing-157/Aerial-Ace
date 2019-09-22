#include <cstdio>

using namespace std;
const unsigned mul = 20190812;

class Magic {
public:
  Magic(unsigned state): state(state), ans(0) {}

  unsigned long long retrieve() {
    unsigned modulo = 0x7fffffff;
    state = ((unsigned long long) state * mul + ans) % modulo;
    unsigned high = state;
    state = ((unsigned long long) state * mul + ans) % modulo;
    return high * modulo + state;
  }

  int retrieve(int a, int b) {
    assert (a <= b);
    return (int) (retrieve() % (b - a + 1)) + a;
  }

  void submit(unsigned k) {
    ans = ans * mul + k;
  }
  
  unsigned retrieveAns() {
    return ans;
  }

private:
  unsigned state, ans;
};

class DataStructure {
public:
  DataStructure() {
    // The data structure is initially empty, until it's not.
    // Implement your initialization here.
  }
  vector<Point> v, conv;
  void build(vector<Point> a)
  {
  	n = v.size();
  	
  }
  void add(int x, int y) {
    // Add a 2D point (x, y) to the DS.
    // Implement your add here.
    
  }
  void erase(int r) {
    // Erase the r-th added point, of all the points that 
    // have still not been erased.
    // Implement your erase here.
  }
  int size() {
    // Return how many points are still in the DS
  }
  pair<int, int> query() {
    // find two points p_i, p_j in the DS (not necessarily distinct),
    // such that the dot product of these two <p_i, p_j> (i <= j) 
    // the smallest among all. Return (i, j).
    // If the DS is empty for now, return (0, 0).
    // Implement your query here.
    // If there are multiple (i, j) satisfying the condition, output the lexicographically smallest pair.

  }
};

int main() {
  const int lim = 1E9;
  int q; cin >> q;
  for (int k = 0; k < q; ++k) {
    unsigned state;
    cin >> state;
    string s;
    cin >> s;
    DataStructure ds;
    Magic magic(state);
    for (char c: s) {
      if (c == 'a') {
        // add one point
        int x = magic.retrieve(-lim, lim);
        int y = magic.retrieve(-lim, lim);
        ds.add(x, y);
      } else if (c == 'e') {
        // select the lucky point
        unsigned pos = magic.retrieve(1, ds.size());
        ds.erase(pos);
      } else if (c == 'q') {
        // query global minimum
        auto best = ds.query();
        magic.submit(best.first);
        magic.submit(best.second);
      }
    }
    cout << magic.retrieveAns() << endl;
  }
  return 0;
}
