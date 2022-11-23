#include <bits/extc++.h>
using namespace std;

/**
 * Polynomial Multiplicant Inverse
 *
 * The inverse technique is mandatory for more advanced poly calculations.
 */

using i64 = long long int;
// NTT arguments. P must be the pattern r*2^k+1, where k must be greater than
// limit.
const i64 P = 998244353, G = 3, Gi = 332748118;
i64 ksm(i64 a, i64 b, i64 mod = P) {
  i64 ret = 1ll;
  while (b) {
    if (b & 1) ret = (ret * a) % mod;
    b >>= 1, a = (a * a) % mod;
  }
  return ret;
}

void NTT(int limit, i64* a, int type, int* r) {
  for (int i = 0; i < limit; ++i)
    if (i < r[i]) swap(a[i], a[r[i]]);  // re-sort
  // accumulate length
  for (int mid = 1; mid < limit; mid <<= 1) {
    i64 Wn = ksm(type == 1 ? G : Gi, (P - 1) / (mid << 1));  // number theory
                                                             // unit
    for (int j = 0; j < limit; j += (mid << 1)) {
      i64 w = 1;
      for (int k = 0; k < mid;
           ++k, w = (w * Wn) % P)  // iterate left half period
      {
        i64 x = a[j + k], y = w * a[j + k + mid] % P;
        a[j + k] = (x + y) % P;
        a[j + k + mid] = (x - y + P) % P;
      }
    }
  }
}

void polyinv(int deg, i64* a, i64* b, int mod) {
  if (deg <= 1) return void(b[0] = ksm(a[0], mod - 2));
  polyinv((deg + 1) >> 1, a, b, mod);
  int limit = 1, l = 0;
  while (limit < deg * 2) limit <<= 1, l++;
  vector<int> r(limit);
  for (int i = 0; i < limit; ++i)
    r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
  vector<i64> c(limit + 1, 0);
  memcpy(c.data(), a, sizeof(i64) * deg);
  // dft
  NTT(limit, c.data(), 1, r.data()), NTT(limit, b, 1, r.data());
  for (int i = 0; i < limit; ++i)
    b[i] = 1ll * (2ll - 1ll * c[i] * b[i] % mod + mod) % mod * b[i] % mod;
  NTT(limit, b, -1, r.data());
  i64 inv = ksm(limit, mod - 2, mod);
  for (int i = 0; i < limit; ++i) b[i] = (b[i] * inv) % mod;
  for (int i = deg; i < limit; ++i) b[i] = 0;
}

int main() {
  int n, capn = 1;
  cin >> n;
  while (capn < 2 * n) capn <<= 1;
  vector<i64> a(capn + 1), b(capn + 1);
  for (int i = 0; i < n; ++i) cin >> a[i];
  polyinv(n, a.data(), b.data(), P);

  for (int i = 0; i < n; ++i) cout << b[i] << ' ';
  cout << endl;

  return 0;
}