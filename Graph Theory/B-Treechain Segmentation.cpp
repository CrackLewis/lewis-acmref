#include <bits/stdc++.h>
using namespace std;

// Implementation based on adjacency linklist.
template <typename WeTy = int>
struct graph1 {
  vector<int> head, to, nxt;
  vector<WeTy> we;
  int n, eid;
  graph1(int _n) : n(_n), head(_n + 1, -1), eid(-1) {}
  void addedge(int u, int v, WeTy w = WeTy()) {
    assert((u >= 1 && v >= 1 && u <= n && v <= n) && "vertex out of range");
    to.emplace_back(v);
    nxt.emplace_back(head[u]);
    we.emplace_back(w);
    head[u] = ++eid;
  }

  /**
   * Treechain Segmentation Algorithm
   *
   * hson: heaviest son (with biggest subtree)
   * id: re-identification (to ensure nodes in the same chain are continuous)
   * fa: father node of a node
   * dep: depth of a node
   * sz: size of a subtree
   * top: top node of the chain the node is located in
   *
   * I used vector reference to avoid memory copying :)
   */
  using VI = vector<int>&;
  void treeseg(int rt, VI hson, VI id, VI fa, VI dep, VI sz, VI top) {
    int cnt = 0;
    hson.resize(n + 1, 0), id.resize(n + 1, 0), fa.resize(n + 1, 0);
    dep.resize(n + 1, 0), sz.resize(n + 1, 0), top.resize(n + 1, 0);

    function<void(int, int, int)> dfs1 = [&](int x, int f, int de) {
      dep[x] = de, fa[x] = f, sz[x] = 1;
      int maxs = -1;
      for (int j = head[x], v; ~j; j = nxt[j]) {
        if ((v = to[j]) == f) continue;
        dfs1(v, x, de + 1);
        sz[x] += sz[v];
        if (sz[v] > maxs) hson[x] = v, maxs = sz[v];
      }
    };
    function<void(int, int)> dfs2 = [&](int x, int topf) {
      id[x] = ++cnt;
      top[x] = topf;
      if (!hson[x]) return;
      dfs2(hson[x], topf);  // extend the heavy chain
      for (int j = head[x], v; ~j; j = nxt[j]) {
        if ((v = to[j]) == fa[x] || v == hson[x]) continue;
        dfs2(v, v);  // for each non-heavy son start a new chain
      }
    };

    dfs1(rt, 0, 1);
    dfs2(rt, rt);
  }
};

/**
 * Treechain Segmentation has a very complicated usage in various tree problems.
 * So a solution to a related problem is provided below.
 *
 * Luogu P3384
 *
 * Given an N-node connected undirected tree with a weight on each node.
 * You need to support 4 different operations on the tree:
 * - 1 x y z : add z to all nodes on the shortest path from x-th node to y-th
 * node.
 * - 2 x y   : query the sum of all nodes on the shortest path from x-th node to
 * y-th node.
 * - 3 x z   : add z to all nodes in the subtree of x-th node.
 * - 4 x     : query the sum of all nodes in the subtree of x-th node.
 *
 * All results of 2nd and 4th operations are modded with P(1<=P<=INT_MAX).
 */
using LL = long long int;
LL MOD;
vector<int> oa, a;
vector<int> hson, id, top, dep, fa, sz;
int n;

struct segtree {
#define lc (x << 1)
#define rc (x << 1 | 1)
#define mid ((l + r) >> 1)

  vector<LL> sum;
  vector<LL> laz;
  segtree(int n) : sum(n * 4 + 5), laz(n * 4 + 5) {}
  void up(int x, int l, int r) { sum[x] = (sum[lc] + sum[rc]) % MOD; }
  void down(int x, int l, int r) {
    if (!laz[x]) return;
    sum[lc] = (sum[lc] + (mid - l + 1) * laz[x]) % MOD, laz[lc] += laz[x];
    sum[rc] = (sum[rc] + (r - mid) * laz[x]) % MOD, laz[rc] += laz[x];
    laz[x] = 0;
  }
  void build(int x, int l, int r) {
    laz[x] = 0;
    if (l >= r) {
      sum[x] = a[l] % MOD;
      return;
    }
    build(lc, l, mid), build(rc, mid + 1, r);
    up(x, l, r);
  }
  void modify(int x, int l, int r, int ll, int rr, int val) {
    if (ll <= l && r <= rr) {
      sum[x] = (sum[x] + ((LL)(r - l + 1)) * val) % MOD;
      laz[x] = (laz[x] + val) % MOD;
      return;
    }
    if (laz[x]) down(x, l, r);
    if (ll <= mid) modify(lc, l, mid, ll, rr, val);
    if (mid + 1 <= rr) modify(rc, mid + 1, r, ll, rr, val);
    up(x, l, r);
  }
  LL query(int x, int l, int r, int ll, int rr) {
    if (ll <= l && r <= rr) return sum[x] % MOD;
    if (laz[x]) down(x, l, r);
    LL ans = 0;
    if (ll <= mid) ans += query(lc, l, mid, ll, rr);
    if (mid + 1 <= rr) ans += query(rc, mid + 1, r, ll, rr);
    return ans % MOD;
  }
  void update_sub(int x, int val) {
    modify(1, 1, n, id[x], id[x] + sz[x] - 1, val);
  }
  void update_path(int sx, int tx, int val) {
    val %= MOD;  // cringe
    while (top[sx] != top[tx]) {
      if (dep[top[sx]] < dep[top[tx]]) swap(sx, tx);
      modify(1, 1, n, id[top[sx]], id[sx], val);
      sx = fa[top[sx]];
    }
    if (dep[sx] > dep[tx]) swap(sx, tx);
    modify(1, 1, n, id[sx], id[tx], val);
  }
  LL query_sub(int x) { return query(1, 1, n, id[x], id[x] + sz[x] - 1); }
  LL query_path(int sx, int tx) {
    LL ans = 0;
    while (top[sx] != top[tx]) {
      if (dep[top[sx]] < dep[top[tx]]) swap(sx, tx);
      ans = (ans + query(1, 1, n, id[top[sx]], id[sx])) % MOD;
      sx = fa[top[sx]];
    }
    if (dep[sx] > dep[tx]) swap(sx, tx);
    ans = (ans + query(1, 1, n, id[sx], id[tx])) % MOD;
    return ans;
  }

#undef lc
#undef rc
#undef mid
};

int main() {
  int m, rt;
  cin >> n >> m >> rt >> MOD;
  oa.resize(n + 1), a.resize(n + 1);
  graph1<int> G(n);
  for (int i = 1; i <= n; ++i) cin >> oa[i];
  for (int i = 1, u, v; i < n; ++i) {
    cin >> u >> v;
    G.addedge(u, v), G.addedge(v, u);
  }
  G.treeseg(rt, hson, id, fa, dep, sz, top);
  // re-sort oa into a
  for (int i = 1; i <= n; ++i) a[id[i]] = oa[i];

  segtree T(n);
  T.build(1, 1, n);
  // deal with queries
  for (int i = 1, op, x, s, t, val; i <= m; ++i) {
    cin >> op;
    if (op == 1) {
      cin >> s >> t >> val;
      T.update_path(s, t, val);
    } else if (op == 2) {
      cin >> s >> t;
      cout << T.query_path(s, t) << endl;
    } else if (op == 3) {
      cin >> x >> val;
      T.update_sub(x, val);
    } else if (op == 4) {
      cin >> x;
      cout << T.query_sub(x) << endl;
    }
  }
  return 0;
}