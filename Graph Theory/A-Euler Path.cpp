/**
 * Regarding to complication of the Euler Route problem,
 * versions in both graph structures are provided below.
 */

// Implementation based on adjacency linklist.
template <typename WeTy = int>
struct graph1 {
  /* Refer to @-Graph Definition */

  // Euler route algorithm
  // if euler()==true, check euler_route for more detailed answer.
  // ==== NOTE ==== This version does not guarantee that the route is
  // in the minimum lexicographical order.
  vector<int> euler_route;
  bool euler() {
    vector<int> deg(n + 1, 0), headp = head;  // deg = deg_out - deg_in
    for (int i = 1, j, v; i <= n; ++i)
      for (j = head[i]; ~j; j = nxt[j]) {
        v = to[j];
        deg[i]++, deg[v]--;
      }

    int euler_start = 0;
    do  // check if an euler route exists
    {
      int first = 0, last = 0;
      for (int i = 1; i <= n; ++i) {
        if (deg[i] < -1 || deg[i] > 1)
          break;
        else if (deg[i] == 1) {
          if (first)
            break;
          else
            first = i;
        } else if (deg[i] == -1) {
          if (last)
            break;
          else
            last = i;
        }
      }
      if (!first && !last)
        euler_start = 1;
      else if (first && last)
        euler_start = first;
      else
        euler_start = 0;
    } while (0);

    if (!euler_start) return false;

    // search function
    function<void(int)> euler_dfs = [&](int x) {
      while (~headp[x]) {
        int v = to[headp[x]];
        headp[x] = nxt[headp[x]];
        euler_dfs(v);
      }
      euler_route.push_back(x);
    };
    euler_dfs(euler_start);
    // route generated was in reverse order, which should be corrected.
    reverse(euler_route.begin(), euler_route.end());
    return int(euler_route.size()) == to.size() + 1;
  }
};

// Implementation based on adjacency array.
template <typename WeTy = int>
struct graph2 {
  /* Refer to @-Graph Definition */

  // Euler route algorithm
  // if euler()==true, check euler_route for more detailed answer.
  // This version guarantees that the route is in the minimum
  // lexicographical order.
  vector<int> euler_route;
  bool euler() {
    int m = 0;
    vector<int> deg(n + 1, 0);
    vector<vector<pair<int, WeTy>>> _e = edges;
    // presort so the algorithm does not blow up
    for (int i = 1; i <= n; ++i) sort(_e[i].rbegin(), _e[i].rend());
    for (int i = 1; i <= n; ++i)
      for (const auto& e : edges[i]) deg[i]++, deg[e.first]--, m++;
    int euler_start = 0;

    // This part is exactly the same as linklist version.
    do  // check if an euler route exists
    {
      int first = 0, last = 0;
      for (int i = 1; i <= n; ++i) {
        if (deg[i] < -1 || deg[i] > 1)
          break;
        else if (deg[i] == 1) {
          if (first)
            break;
          else
            first = i;
        } else if (deg[i] == -1) {
          if (last)
            break;
          else
            last = i;
        }
      }
      if (!first && !last)
        euler_start = 1;
      else if (first && last)
        euler_start = first;
      else
        euler_start = 0;
    } while (0);

    if (!euler_start) return false;

    function<void(int)> euler_dfs = [&](int x) {
      while (_e[x].size()) {
        int v = (--_e[x].end())->first;
        _e[x].pop_back();
        euler_dfs(v);
      }
      euler_route.push_back(x);
    };
    euler_dfs(euler_start);
    // route generated was in reverse order, which should be corrected.
    reverse(euler_route.begin(), euler_route.end());
    return int(euler_route.size()) == m + 1;
  }
};