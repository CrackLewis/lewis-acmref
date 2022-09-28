#include <bits/stdc++.h>
using namespace std;

using LL = long long int;
LL gcd(LL a, LL b);
/**
 * Bezout Theory
 *
 * There exists X[1...n] which satisfies \sum_{i=1}^n {A_i*X_i} =
 * \gcd(A_1,A_2,...,A_n). The function bezout(A) returns the minimum positive
 * value of \sum_{i=1}^n {A_i*X_i}. (A_i != 0)
 */
LL bezout(const vector<LL>& A) {
  LL res = -1;
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