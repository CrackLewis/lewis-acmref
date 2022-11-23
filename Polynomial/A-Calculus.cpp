#include <bits/extc++.h>
using namespace std;

/**
 * Calculus mainly involves derivation and integration in polynomials.
 */

using i64 = long long int;
i64 ksm(i64 a, i64 b, i64 mod) {
  i64 ans = 1;
  while (b) {
    if (b & 1) ans = (ans * a) % mod;
    b >>= 1, a = (a * a) % mod;
  }
  return ans;
}

vector<i64> get_derive(const vector<i64>& a, i64 mod) {
  vector<i64> b(a.size(), 0);
  for (int i = 1, _i = a.size(); i < _i; ++i) {
    b[i - 1] = 1ll * i * a[i] % mod;
  }
  return b;
}

vector<i64> get_integrate(const vector<i64>& a, i64 mod) {
  vector<i64> b(a.size(), 0);
  for (int i = 1, _i = a.size(); i < _i; ++i) {
    b[i] = a[i - 1] * ksm(i % mod, mod - 2, mod) % mod;
  }
  return b;
}