#include <bits/stdc++.h>
using namespace std;

using LL = long long int;
LL exgcd(LL a, LL b, LL& x, LL& y) {
  if (!b) {
    x = 1, y = 0;
    return a;
  }
  LL ret = exgcd(b, a % b, y, x);
  y -= (a / b) * x;
  return ret;
}

/**
 * Chinese Remainder Theory (CRT)
 *
 * a method dedicated to solve remainder equation group like this:
 * x%3=2,x%5=3,x%7=1,x%9=2,...
 *
 * In function CRT(a,r), a[i] is the remainder and r[i] is the mod of the i-th
 * equation.
 */
LL CRT(const vector<LL>& a, const vector<LL>& r) {
  assert(a.size() == r.size() && a.size() > 0);
  LL N = 1, ans = 0, n = a.size();
  // 1. Calculate N=\prod r[i].
  for (int i = 0; i < n; ++i) N = N * r[i];
  // 2. for every equation:
  for (int i = 0; i < n; ++i) {
    //(1) Calculate M=N/r[i]
    LL m = N / r[i], b, y;
    //(2) Calculate inverse of M mod r[i]
    exgcd(m, r[i], b, y);
    //(3) Calculate c_i = M_inv * M
    ans = (ans + a[i] * m * b % N) % N;
  }
  // 3. Sum up the answer = \sum {c_i * a_i}.
  return (ans % N + N) % N;
}

// Luogu P1495
int main() {
  int n;
  cin >> n;
  vector<LL> r(n), a(n);
  LL rprod = 1ll;
  for (int i = 0; i < n; ++i) cin >> r[i] >> a[i], rprod *= r[i];
  cout << CRT(a, r) % rprod << endl;
  return 0;
}