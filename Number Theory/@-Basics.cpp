/**
 * Number Theory Basics
 *
 * - gcd (greatest common divisor)
 * - exgcd (extended GCD)
 * - ksm/gsc (quickpower/slow(but-robust) mul)
 * - m_inv (multiplicative inverse)
 * - frac_rd (fraction reduction: 3/6 => 1/2)
 */

#include <bits/stdc++.h>
using namespace std;

using i64 = long long int;
const i64 MOD998 = 998244353;
const i64 MOD107 = 1000000007;
// ATTENTION: You need to modify MOD to problem specific values.
const i64 MOD = MOD998;

i64 gcd(i64 a, i64 b) { return b ? gcd(b, a % b) : a; }

i64 exgcd(i64 a, i64 b, i64& x, i64& y) {
  if (!b) {
    x = 1, y = 0;
    return a;
  }
  i64 ret = exgcd(b, a % b, y, x);
  y -= (a / b) * x;
  return ret;
}

// returns (a**b)%MOD, a,b in INT32
i64 ksm(i64 a, i64 b, i64 mod = MOD) {
  i64 ret = 1ll;
  while (b) {
    if (b & 1) ret = (ret * a) % mod;
    b >>= 1, a = (a * a) % mod;
  }
  return ret;
}

// returns (a*b)%MOD, a,b in INT64
i64 gsc(i64 a, i64 b, i64 mod = MOD) {
  i64 ret = 0ll;
  while (b) {
    if (b & 1) ret = (ret + a) % mod;
    a = (a + a) % mod, b >>= 1;
  }
  return ret;
}

// returns mult-inverse of x
// using fermat little theorem: a^(p-1)===1 (mod p)
i64 m_inv(i64 x, i64 mod = MOD) { return ksm(x % mod, mod - 2) % mod; }

// fraction reduction
void frac_rd(i64& dend, i64& dor) {
  assert(dor != 0);
  if (dend == 0) dor = 1;
  int f = 1;
  if (dend < 0) dend = -dend, f = -f;
  if (dor < 0) dor = -dor, f = -f;
  i64 _gcd = gcd(dend, dor);
  dend /= _gcd, dor /= _gcd;
  dend *= f;
}