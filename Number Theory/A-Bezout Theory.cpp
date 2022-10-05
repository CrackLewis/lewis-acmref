#include <bits/stdc++.h>
using namespace std;

using i64 = long long int;
i64 gcd(i64 a, i64 b);
/**
 * Bezout Theory
 *
 * There exists X[1...n] which satisfies \sum_{i=1}^n {A_i*X_i} =
 * \gcd(A_1,A_2,...,A_n). The function bezout(A) returns the minimum positive
 * value of \sum_{i=1}^n {A_i*X_i}. (A_i != 0)
 */
i64 bezout(const vector<i64>& A) {
  i64 res = -1;
  for (auto i : A) {
    if (i == 0) continue;
    if (i < 0) i = -i;
    if (res == -1)
      res = i;
    else
      res = gcd(res, i);
  }
  return res;
}