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

  BipartiteDyeingDSU(int _n) : n(_n), DSU(2 * _n) {}

  void merge(int u, int v, int flg) {
    if (flg)
      DSU::merge(u, v + n), DSU::merge(u + n, v);
    else
      DSU::merge(u, v), DSU::merge(u + n, v + n);
  }

  int result() {
    for (int i = 1; i <= n; ++i)
      if (find(i) == find(i + n)) return 0;
    return 1;
  }
};