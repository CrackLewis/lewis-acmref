#include <bits/stdc++.h>
using namespace std;

/**
 * BIT K-th smallest element
 *
 * BIT solution is a popular one to the K-th smallest element problem.
 *
 */
struct BIT {
#define lowbit(x) ((x) & (-x))
  int n;
  vector<int> c;

  BIT(int _n) : c(_n + 1), n(_n) {}

  void add(int pos, int val) {
    while (pos <= n) {
      c[pos] += val;
      pos += lowbit(pos);
    }
  }

  int getsum(int x)  //[1-x]
  {
    int ret = 0;
    while (x) {
      ret += c[x];
      x -= lowbit(x);
    }
    return ret;
  }

  // Example of the K-th smallest problem
  void insert(int val) { add(val, 1); }
  int kth(int k) {
    int cnt = 0, ret = 0;
    for (int i = log2(n); ~i; --i) {
      ret += (1 << i);
      if (ret >= n || cnt + c[ret] >= k)
        ret -= (1 << i);
      else
        cnt += c[ret];
    }
    return ret + 1;
  }
#undef lowbit
};

void kth_demo() {
  // the data range is very limited, so discretion might be feasible.
  BIT bit(1000);
  int _;
  cin >> _;
  while (_--) {
    int x;
    cin >> x;
    bit.insert(x);
  }
  cin >> _;
  while (_--) {
    int k;
    cin >> k;
    cout << bit.kth(k) << endl;
  }
}