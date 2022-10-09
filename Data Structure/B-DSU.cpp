#include <bits/stdc++.h>
using namespace std;

/**
 * Disjoint Set Union
 *
 * A tricky but useful structure in various problems.
 */

struct DSU {
  int n;
  vector<int> fa;
  DSU(int _n) : n(_n), fa(_n + 1, 0) {
    for (int i = 1; i <= n; ++i) fa[i] = i;
  }
  int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
  void merge(int x, int y) {
    x = find(x), y = find(y);
    if (x != y) fa[y] = x;
  }
};

/**
 * Bipartite Dyeing Problem in DSU Method
 *
 * Input: all edges in the bipartite graph (w=0:same side,w=1:opposed)
 * Output: dyeing result or report a conflict
 */
struct BipartiteDyeingDSU : public DSU {
  int n;

  BipartiteDyeingDSU(int _n, const vector<tuple<int, int, int>>& edges)
      : n(_n), DSU(2 * _n) {
    // this part uses C++17 grammar
    for (auto [u, v, we] : edges) {
      if (we)
        merge(u, v + n), merge(u + n, v);
      else
        merge(u, v), merge(u + n, v + n);
    }
  }

  int result(vector<int>& res) {
    for (int i = 1; i <= n; ++i)
      if (find(i) == find(i + n)) return 0;
    res.resize(n + 1, 0);
    // same sided with 1 is named side 0
    for (int i = 1; i <= n; ++i) res[i] = !(find(i) == find(1));
    return 1;
  }
};