#include <bits/stdc++.h>
using namespace std;

/**
 * Integer Factorization Algorithm - Pollard-Rho
 *
 * The common factorization method which is O(sqrt(n)):
 * Iterate all i in [1,sqrt(n)] to test if n%i==0.
 * If we have a prime table the method complexity is O(sqrt(n)/ln(n)).
 *
 * When n goes too large it is impossible to absolutely confirm all factorials.
 * But we can still perform PRIME TESTS to get ALMOST all of them.
 *
 * The core idea of factorization is *** Pollard-Rho *** algorithm.
 * Pollard-rho algorithm tries to find a factor of x.
 * Formally, it attempts to find a k in the rho-loop of [0,x-1] which satisfies
 * gcd(k,x)>1, which indicates that x%k==0.
 *
 * Miller-Rabin method is the PRIMALITY TEST method used in Pollard-rho.
 * It relies on the fermat theory and quad-detection theory to ensure
 * correctness.
 */

using i64 = long long int;
i64 gcd(i64 a, i64 b) { return b ? gcd(b, a % b) : a; }
/**
 * Why using a lot of __int128_t here?
 * Because we want to do quickpow on i64 type, which needs int128 for temporary
 * storage. (Guisucheng is shit)
 */
i64 ksm(i64 a, i64 b, i64 mod) {
  i64 res = 1ll;
  while (b) {
    if (b & 1) res = ((__int128_t)res * a) % mod;
    b >>= 1, a = ((__int128_t)a * a) % mod;
  }
  return res;
}
// Miller-Rabin test
i64 miller_rabin(i64 x, i64 b) {
  i64 k = x - 1;
  while (k) {
    i64 cur = ksm(b, k, x);
    // violates the quad-detection
    if (cur != 1 && cur != x - 1) return false;
    if ((k & 1) == 1 || cur == x - 1) return true;
    k >>= 1;
  }
  return true;
}
// primality test
bool isprime(i64 x) {
  // the only failed case in our approach is 46856248255981.
  // so it's specially listed here.
  if (x == 46856248255981ll || x < 2) return false;
  if (x == 2 || x == 3 || x == 7 || x == 61 || x == 24251) return true;
  return miller_rabin(x, 2) && miller_rabin(x, 61);
}
// transform used in pollard-rho
i64 f(i64 x, i64 c, i64 n) { return ((__int128_t)x * x + c) % n; }
// the god rolls a dice
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
// pollard_rho(x): returns a factor of x
i64 pollard_rho(i64 x) {
  i64 s = 0, t = 0, c = 1ll * rnd() % (x - 1) + 1;
  int stp = 0, goal = 1;
  i64 val = 1;
  for (goal = 1; goal; goal <<= 1, s = t, val = 1) {
    for (stp = 1; stp <= goal; ++stp) {
      t = f(t, c, x);
      val = (__int128_t)val * abs(t - s) % x;
      if ((stp % 127) == 0) {
        i64 d = gcd(val, x);
        if (d > 1) return d;
      }
    }
    i64 d = gcd(val, x);
    if (d > 1) return d;
  }
  return x;
}

/**
 * Example.
 *
 * factorize() generates a list of factors of x.
 */
map<i64, int> factors;
void factorize(i64 x, i64 pw = 1) {
  if (x < 2) return;
  if (isprime(x)) {
    factors[x] += pw;
    return;
  }
  i64 p = x, ppw = 0;
  while (p >= x) p = pollard_rho(x);
  while ((x % p) == 0) x /= p, ppw++;
  // split factors
  factorize(x, pw), factorize(p, pw * ppw);
}

int main() {
  i64 x;
  int _;
  cin >> _;
  while (_--) {
    cin >> x;
    factors.clear();
    factorize(x);
    cout << x << '=';
    bool frstar = false;
    for (auto& pr : factors) {
      if (frstar)
        cout << '*';
      else
        frstar = true;
      cout << pr.first;
      if (pr.second > 1) cout << '^' << pr.second;
    }
    cout << endl;
  }
  return 0;
}