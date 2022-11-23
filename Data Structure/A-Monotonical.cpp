#include <bits/extc++.h>
using namespace std;

/**
 * Monotonical Sequences
 *
 * Monotonical sequences (especially queue and stack) are commonly used as an
 * optimization in dynamic programming.
 */

/**
 * Example.
 * Given an array a[1:n] and integer k, for every i in [1,n-k+1], calculate
 * min(f(a[i:i+k-1])). We use f(x)=(x-4)*(x-4)*(x-3) as the example.
 */
using i64 = long long int;
vector<i64> mono_queue(const vector<int>& a, int k) {
  auto f = [&](int x) { return 1ll * (x - 4) * (x - 4) * (x - 3); };
  deque<int> Q;
  vector<i64> ans;
  int n = a.size();
  for (int i = 0; i < n; ++i) {
    // pop the outdated elements: indices x which satisfies x<=i-k.
    while (Q.size() && Q.front() <= i - k) Q.pop_front();
    // insert new element and maintain the monotonicity.
    while (Q.size() && f(a[Q.back()]) > f(a[i])) Q.pop_back();
    Q.push_back(i);
    if (i >= k - 1) ans.emplace_back(f(a[Q.front()]));
  }
  return ans;
}

/**
 * Example.
 * Calculate for each a[i] the position of the first j which satisfies a[j]>a[i]
 * and j>i. If the position does not exist then the answer will be n.
 */
vector<int> mono_stack(const vector<int>& a) {
  int n = a.size();
  vector<int> ans(n);
  stack<int> S;
  for (int i = n - 1; i >= 0; --i) {
    // maintain the monotonicity.
    while (!S.empty() && a[S.top()] <= a[i]) S.pop();
    ans[i] = S.empty() ? n : S.top();
    S.push(i);
  }
  return ans;
}