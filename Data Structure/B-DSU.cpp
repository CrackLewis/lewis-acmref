#include <bits/stdc++.h>
using namespace std;

/**
 * Disjoint Set Union
 *
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