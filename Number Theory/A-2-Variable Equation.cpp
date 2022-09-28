#include <bits/stdc++.h>
using namespace std;

using LL = long long int;
LL exgcd(LL a, LL b, LL& x, LL& y);

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
int equat2(LL a, LL b, LL c, LL& scnt, LL& x1, LL& x2, LL& y1, LL& y2) {
  LL x, y;
  LL res = exgcd(a, b, x, y);
  // if gcd(a,b) cannot divide c, then there is no integer solution
  if (c % res) return 0;

  // now (x,y) is a solution for ax+by=gcd(a,b)
  // adjust x into the smallest positive integer
  x *= (c / res), y *= (c / res);
  LL p = b / res, q = a / res;
  if (x < 0) {
    LL rate = ceil((1.0 - x) / p);
    x += p * rate, y -= q * rate;
  } else {
    LL rate = (x - 1) / p;
    x -= p * rate, y += q * rate;
  }

  if (y > 0) {
    scnt = (y - 1) / q + 1;
    x1 = x, x2 = x + (y - 1) / q * p;
    y1 = (y - 1) % q + 1, y2 = y;
    return 2;
  }
  x1 = x, y1 = y + q * (LL)ceil((1.0 - y) / q);
  return 1;
}