#include <bits/extc++.h>
using namespace std;

using i64 = long long int;

ostream& operator<<(ostream& out, const vector<i64>& a) {
  for (auto i : a) cout << i << ' ';
  return out;
}
void debug() { cout << endl; }
template <typename T1, typename... T2>
void debug(T1 a, T2... oth) {
  cout << a << ' ';
  debug(oth...);
}
#define Debug(...)                                              \
  cout << setw(12) << __FILE__ << setw(6) << __LINE__ << " # ", \
      debug(__VA_ARGS__)

namespace Polyn {
vector<int> r[28];
int limit, l;
const vector<int>& get_limit(int n) {
  limit = 1, l = 0;
  while (limit <= n) limit <<= 1, l++;
  if (r[l].size() <= 0) {
    r[l].resize(limit, 0);
    for (int i = 0; i < limit; i++)
      r[l][i] = (r[l][i >> 1] >> 1) | ((i & 1) << (l - 1));
  }
  return r[l];
}
}  // namespace Polyn

const i64 P = 998244353, G = 3, Gi = 332748118;
i64 ksm(i64 a, i64 b, i64 mod = P) {
  i64 ret = 1ll;
  while (b) {
    if (b & 1) ret = (ret * a) % mod;
    b >>= 1, a = (a * a) % mod;
  }
  return ret;
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

void ntt(vector<i64>& a, int type) {
  const vector<int>& r = Polyn::get_limit(a.size() - 2);  // limit-1
  int limit = Polyn::limit;
  for (int i = 0; i < limit; ++i)
    if (i < r[i]) swap(a[i], a[r[i]]);
  for (int mid = 1; mid < limit; mid <<= 1) {
    i64 Wn = ksm(type == 1 ? G : Gi, (P - 1) / (mid << 1));
    for (int j = 0; j < limit; j += (mid << 1)) {
      i64 w = 1;
      for (int k = 0; k < mid; ++k, w = (w * Wn) % P) {
        i64 x = a[j + k], y = w * a[j + k + mid] % P;
        a[j + k] = (x + y) % P;
        a[j + k + mid] = (x - y + P) % P;
      }
    }
  }
  if (type == -1) {
    i64 inv = ksm(limit, P - 2) % P;
    for (int i = 0; i < limit; ++i) a[i] = (a[i] * inv) % P;
  }
}

vector<i64> get_ntt(const vector<i64>& a, int type) {
  vector<i64> b = a;
  ntt(b, type);
  return b;
}

void inv(const vector<i64>& a, vector<i64>& b, int n) {
  if (n == 1) {
    b[0] = ksm(a[0], P - 2);
    return;
  }
  // Debug(n);
  inv(a, b, n >> 1);
  Polyn::get_limit(n);
  int limit = Polyn::limit;
  // Debug(n, limit);
  //  consider using static array if mle/tle is encountered
  vector<i64> c(limit + 1), d(limit + 1);
  for (int i = 0; i < n; ++i) c[i] = a[i], d[i] = b[i];
  for (int i = n; i < limit; ++i) c[i] = d[i] = 0;
  ntt(c, 1), ntt(d, 1);
  for (int i = 0; i < limit; ++i) c[i] = 1ll * c[i] * d[i] % P * d[i] % P;
  ntt(c, -1);
  // value exceeding n is discarded
  for (int i = 0; i < n; ++i) b[i] = ((2ll * b[i] % P - c[i]) % P + P) % P;
  for (int i = n; i < b.size(); ++i) b[i] = 0;
}

vector<i64> get_inv(const vector<i64>& a, int n) {
  vector<i64> b(a.size(), 0);
  inv(a, b, n);
  return b;
}

vector<i64> get_ln(const vector<i64>& a, int n) {
  auto r = Polyn::get_limit(n);
  int limit = Polyn::limit;
  auto A = get_derive(a, P), B = get_inv(a, n);
  A.resize(limit + 1), B.resize(limit + 1);
  ntt(A, 1), ntt(B, 1);
  for (int i = 0; i < limit; ++i) A[i] = 1ll * A[i] * B[i] % P;
  ntt(A, -1);
  auto C = get_integrate(A, P);
  C.resize(a.size());
  return C;
}

int main() {
  int n;
  cin >> n;
  Polyn::get_limit(n);
  vector<i64> a(Polyn::limit + 1);
  for (int i = 0; i < n; ++i) cin >> a[i];
  // Debug(a.size(), a);

  auto b = get_ln(a, Polyn::limit);
  for (int i = 0; i < n; ++i) cout << b[i] << ' ';
  cout << endl;
  return 0;
}