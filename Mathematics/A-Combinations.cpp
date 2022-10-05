#include <bits/extc++.h>
using namespace std;

using i64 = long long int;

i64 ksm(i64 a, i64 b, i64 mod) {
  i64 ret = 1ll;
  while (b) {
    if (b & 1) ret = (ret * a) % mod;
    b >>= 1, a = (a * a) % mod;
  }
  return ret;
}

struct Combn {
  vector<i64> fac, ifac;
  i64 n, mod;
  Combn(int _n, i64 _mod) : n(_n), fac(_n + 1), ifac(_n + 1), mod(_mod) {
    fac[0] = 1;
    for (int i = 1; i <= _n; ++i) fac[i] = (fac[i - 1] * i) % _mod;
    ifac[_n] = ksm(fac[_n] % _mod, _mod - 2, _mod);
    for (int i = _n - 1; i >= 0; --i) ifac[i] = (ifac[i + 1] * (i + 1)) % _mod;
  }

  // C(m,n)=n!/(m!(n-m)!)
  i64 C(i64 m, i64 n) { return fac[n] * ifac[m] % mod * ifac[n - m] % mod; }
  // A(m,n)=n!/(n-m)!
  i64 A(i64 m, i64 n) { return fac[n] * ifac[n - m] % mod; }
};