// Implementation based on adjacency linklist.
template <typename WeTy = int>
struct graph1 {
  /* Refer to @-Graph Definition */

  /**
   * Tree Diameter Algorithm
   *
   * The function diameter() implemented DP on tree to calculate the top-2
   * longest path in the subtree, which could later merge into a legal path. The
   * diameter is always equal to the longest path on the tree.
   */
  WeTy diameter() {
    vector<WeTy> d1(n + 1, 0), d2(n + 1, 0);
    WeTy d = WeTy(), t;

    function<void(int, int)> dfs = [&](int u, int fa) {
      d1[u] = d2[u] = 0;
      for (int j = head[u], v; ~j; j = nxt[j]) {
        if ((v = to[j]) == fa) continue;
        dfs(v, u);
        t = d1[v] + we[j];
        if (t > d1[u])
          d2[u] = d1[u], d1[u] = t;
        else if (t > d2[u])
          d2[u] = t;
      }
      d = max(d, d1[u] + d2[u]);
    };
    dfs(1, 0);
    return d;
  }
};