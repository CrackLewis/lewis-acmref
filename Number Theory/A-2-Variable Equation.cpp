#include <bits/stdc++.h>
using namespace std;

using i64 = long long int;
i64 exgcd(i64 a, i64 b, i64& x, i64& y);

/**
 * 2-Variable Equation (ax+by=c, a,b,c>0)
 *
 * return: verdict
 * - 0: does not have an integer solution.
 * - 1: has integer solutions, but no positive one.
 * - 2: has positive integer solutions.
 *
 * args:
 * - a,b,c: equation parameter (a,b,c>0)
 * - scnt: the number of positive integer solutions.
 * - x1,x2: mininum and maximum positive value of x
 * - y1,y2: minimum and maximum positive value of y
 * scnt,x2,y2 only effective when return>=2
 * x1,y1 only effective when return>=1
 */
int equat2(i64 a, i64 b, i64 c, i64& scnt, i64& x1, i64& x2, i64& y1, i64& y2) {
  i64 x, y;
  i64 res = exgcd(a, b, x, y);
  // if gcd(a,b) cannot divide c, then there is no integer solution
  if (c % res) return 0;

  // now (x,y) is a solution for ax+by=gcd(a,b)
  // adjust x into the smallest positive integer
  x *= (c / res), y *= (c / res);
  i64 p = b / res, q = a / res;
  if (x < 0) {
    i64 rate = ceil((1.0 - x) / p);
    x += p * rate, y -= q * rate;
  } else {
    i64 rate = (x - 1) / p;
    x -= p * rate, y += q * rate;
  }

  if (y > 0) {
    scnt = (y - 1) / q + 1;
    x1 = x, x2 = x + (y - 1) / q * p;
    y1 = (y - 1) % q + 1, y2 = y;
    return 2;
  }
  x1 = x, y1 = y + q * (i64)ceil((1.0 - y) / q);
  return 1;
}