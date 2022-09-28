#include <bits/stdc++.h>
using namespace std;

/**
 * Linear prime sieve
 *
 * O(n) method to pick all primes and calculate vphi,mu function values in range
 * [1,n].
 */
void linear_sieve(vector<int>& vphi,    // ==> vphi[1~n]
                  vector<int>& mu,      // ==> mu[1~n]
                  vector<int>& primes,  // primes is base-1.
                  int n) {
  assert(n > 0);
  // pre-size the arrays
  vphi.resize(n + 1), mu.resize(n + 1), primes.emplace_back(0);
  vector<bool> vis(n + 1, false);
  int cnt = 0;

  mu[1] = vphi[1] = 1;
  // iterate all ints in [2,i]
  for (int i = 2; i <= n; ++i) {
    if (!vis[i]) primes.emplace_back(i), mu[i] = -1, vphi[i] = i - 1, cnt++;
    // i*primes[j] will always be non-prime
    for (int j = 1; j <= cnt && primes[j] * i <= n; ++j) {
      vis[primes[j] * i] = true;
      // if primes[j] can divide i
      if (i % primes[j] == 0) {
        vphi[i * primes[j]] = vphi[i] * primes[j];
        // original template has a useless statement here:
        // mu[i*primes[j]]=0;
        break;
      }
      // or phi(ip)=(p-1)*phi(i),mu(ip)=mu(p)*mu(i)=-mu(i)
      vphi[i * primes[j]] = vphi[primes[j]] * vphi[i];
      mu[i * primes[j]] = -mu[i];
    }
  }
  // ATTENTION: You might need the prefix sum version of the array vphi and mu.
  // If you do so, remember to mark vphi as LL type.
}