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
   * Bridge Algorithm
   *
   * A bridge is an edge in an undirected connected graph without which the
   * located connected component will fall apart.
   *
   * Returns flag: flag[i] is 0 if the edge between the i-th node and its father
   * is not a bridge, otherwise, flag[i] equals to the id of the father node.
   */
  vector<int> bridge() {
    vector<int> vis(n + 1), flag(n + 1), dfn(n + 1), low(n + 1), father(n + 1);
    int nid = 0, res = 0;
    // we need tarjan method to get dfn and low
    function<void(int, int)> tarjan_dfs = [&](int u, int fa) {
      father[u] = fa;
      vis[u] = 1;
      low[u] = dfn[u] = ++nid;
      for (int j = head[u], v; ~j; j = nxt[j]) {
        v = to[j];
        if (!vis[v]) {  // unvisited
          tarjan_dfs(v, u);
          low[u] = min(low[u], low[v]);
          if (low[v] > dfn[u]) {
            flag[u] = father[u];
            res++;
          }
        } else if (dfn[v] < dfn[u] && v != fa) {
          low[u] = min(low[u], dfn[v]);
        }
      }
    };

    for (int i = 1; i <= n; ++i) {
      if (!vis[i]) {
        nid = 0;
        tarjan_dfs(i, i);
      }
    }
    return flag;
  }
};