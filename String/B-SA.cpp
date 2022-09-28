#include <bits/stdc++.h>
using namespace std;

/**
 * SA (Suffix Array)
 *
 * rk[i]: rank of S[i-1:n-1] of all suffixes of S
 * sa[i]: suffix id ranking i-th of all suffixes
 */

int SuffixArray(const string& S, vector<int>& rk, vector<int>& sa) {
  int i, m = 300, p = 0, w, n = S.length();
  // px[i]=rk[id[i]]
  vector<int> oldrk(2 * n + 1, 0), id(n + 1, 0), px(n + 1, 0), cnt(m + 1, 0);
  rk.resize(2 * n + 1, 0);
  sa.resize(n + 1, 0);

  auto cmp = [&](int x, int y, int w) {
    return oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w];
  };

  // solve single character rank.
  for (i = 1; i <= n; ++i) ++cnt[rk[i] = S[i - 1]];
  for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
  for (i = n; i >= 1; --i) sa[cnt[rk[i]]--] = i;

  // iterate w
  for (w = 1;; w <<= 1, m = p) {  // m=p does value range optimization
    for (p = 0, i = n; i > n - w; --i) id[++p] = i;
    for (i = 1; i <= n; ++i)
      if (sa[i] > w) id[++p] = sa[i] - w;
    cnt.assign(m + 1, 0);
    for (i = 1; i <= n; ++i) ++cnt[px[i] = rk[id[i]]];
    for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
    for (i = n; i >= 1; --i) sa[cnt[px[i]]--] = id[i];
    oldrk = rk;
    for (p = 0, i = 1; i <= n; ++i)
      rk[sa[i]] = cmp(sa[i], sa[i - 1], w) ? p : ++p;
    if (p == n) {
      for (int i = 1; i <= n; ++i) sa[rk[i]] = i;
      break;
    }
  }

  return 0;
}