#include <bits/extc++.h>
using namespace std;

using i64 = long long int;
using LD = long double;

/**
 * Why MTT?
 *
 * FFT and NTT are two most popular polynomial methods, but they both have
 * drawbacks to varying degrees.
 * FFT lacks accuracy but has relatively high data bound, whereas NTT ensures
 * accuracy but lacks data bound.
 * MTT is a method which can deal with higher data bounds in sacrifice of time
 * complexity.
 *
 * The following example is poly multiplication in random mod (not necessarily
 * prime).
 */

const LD PI = acos(-1.0);
struct Complex {
  LD r, i;
  Complex(LD _r = 0, LD _i = 0) : r(_r), i(_i) {}
};
Complex operator+(const Complex& a, const Complex& b) {
  return Complex(a.r + b.r, a.i + b.i);
}
Complex operator-(const Complex& a, const Complex& b) {
  return Complex(a.r - b.r, a.i - b.i);
}
Complex operator*(const Complex& a, const Complex& b) {
  return Complex(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r);
}

void FFT(int limit, Complex* a, int type, const vector<int>& r) {
  // re-sort the array into iteration sequence
  for (int i = 0; i < limit; ++i)
    if (i < r[i]) swap(a[i], a[r[i]]);
  // iterate merging period length from 1 to limit/2
  for (int mid = 1; mid < limit; mid <<= 1) {
    Complex Wn(cos(PI / mid), type * sin(PI / mid));  // complex unit
    for (int R = mid << 1, j = 0; j < limit; j += R)  // period [j,j+R)
    {
      Complex w(1, 0);
      // iterate left half
      for (int k = 0; k < mid; ++k, w = w * Wn) {
        Complex x = a[j + k], y = w * a[j + mid + k];  // butterfly effect lol
        a[j + k] = x + y;
        a[j + mid + k] = x - y;
      }
    }
  }
  if (type == -1) {
    for (int i = 0; i < limit; ++i) a[i].r /= limit, a[i].i /= limit;
  }
}

void MTT(int limit, i64 mod, i64* lhs, i64* rhs, i64* ret,
         const vector<int>& r) {
  vector<Complex> A(limit + 1), B(limit + 1), C(limit + 1), D(limit + 1),
      E(limit + 1), F(limit + 1), G(limit + 1), H(limit + 1);
  for (int i = 0; i < limit; ++i) {
    lhs[i] %= mod, rhs[i] %= mod;
    A[i] = Complex(lhs[i] >> 15), B[i] = Complex(lhs[i] & 0x7fff);
    C[i] = Complex(rhs[i] >> 15), D[i] = Complex(rhs[i] & 0x7fff);
  }
  FFT(limit, A.data(), 1, r);
  FFT(limit, B.data(), 1, r);
  FFT(limit, C.data(), 1, r);
  FFT(limit, D.data(), 1, r);
  for (int i = 0; i < limit; ++i) {
    E[i] = A[i] * C[i];
    F[i] = B[i] * C[i];
    G[i] = A[i] * D[i];
    H[i] = B[i] * D[i];
  }
  FFT(limit, E.data(), -1, r);
  FFT(limit, F.data(), -1, r);
  FFT(limit, G.data(), -1, r);
  FFT(limit, H.data(), -1, r);
  i64 e, f, g, h;
  for (int i = 0; i < limit; ++i) {
    e = ((((i64)(E[i].r + 0.5)) % mod) << 30) % mod;
    f = ((((i64)(F[i].r + 0.5)) % mod) << 15) % mod;
    g = ((((i64)(G[i].r + 0.5)) % mod) << 15) % mod;
    h = (((i64)(H[i].r + 0.5)) % mod);
    ret[i] = (e + f + g + h) % mod;
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  i64 n, m, mod, limit = 1, l = 0;
  cin >> n >> m >> mod;
  while (limit <= n + m) limit <<= 1, l++;
  vector<i64> a(limit + 1, 0), b(limit + 1, 0), c(limit + 1, 0);
  for (int i = 0; i <= n; ++i) cin >> a[i];
  for (int i = 0; i <= m; ++i) cin >> b[i];
  vector<int> r(limit);
  for (int i = 0; i < limit; ++i)
    r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
  MTT(limit, mod, a.data(), b.data(), c.data(), r);
  for (int i = 0; i <= n + m; ++i) cout << c[i] << ' ';
  cout << endl;
  return 0;
}