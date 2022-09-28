#include <bits/stdc++.h>
using namespace std;

struct ST_table {
  const static int pmax = 19;
  int n;
  vector<int> st[pmax];
  vector<int> pow;

  ST_table(const vector<int>& a) : n(a.size()), pow(pmax) {
    pow[0] = 1;
    for (int i = 1; i < pmax; ++i) pow[i] = pow[i - 1] << 1;
    st[0] = a;
    for (int i = 1; i < pmax; ++i) {
      st[i].resize(a.size(), 0);
      for (int j = 0, _j = a.size() - pow[i]; j <= _j; j++)
        st[i][j] = max(st[i - 1][j], st[i - 1][j + pow[i - 1]]);
    }
  }

  int query(int l, int r) {
    int m = log2(r - l + 1);
    return max(st[m][l], st[m][r - pow[m] + 1]);
  }
};

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  for (int& i : a) cin >> i;
  ST_table st(a);
  int l, r;
  while (m--) {
    cin >> l >> r;
    cout << st.query(l - 1, r - 1) << '\n';
  }
  return 0;
}