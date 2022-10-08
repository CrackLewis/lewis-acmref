#include <bits/extc++.h>
using namespace std;

/**
 * What are QoL Math functions?
 *
 * Using math functions like sqrt,floor,ceil,log... in integer calculations is
 * almost never a good idea. So these functions can really help if test failures
 * are encountered.
 */

using i64 = long long int;
// ceil(a/b)
i64 ceilfrac(i64 a, i64 b) { return (a + b - 1) / b; }
// floor(a/b)
i64 floorfrac(i64 a, i64 b) { return a / b; }
// floor(sqrt(a))
i64 isqrt(i64 x) {
  i64 ans = 0;
  for (i64 k = 1LL << 30; k != 0; k /= 2) {
    if ((ans + k) * (ans + k) <= x) {
      ans += k;
    }
  }
  return ans;
}
// ceil(log(a)): use __lg(a) or __builtin_clzll(a) method
i64 ilog2(i64 x) { return __lg(x); }