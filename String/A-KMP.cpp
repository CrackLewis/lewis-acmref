#include <bits/stdc++.h>
using namespace std;

/**
 * Knuth-Morris-Pratt (KMP) Algorithm
 *
 * KMP is famous for its ability to check all presences of the pattern string in
 * the text in O(nlogn) time complexity.
 *
 * The function kmp_build(const string& str) returns the fail
 * function(fail[0]~fail[n]) of str. Fail function indicates the next position
 * to match if the current match fails. Specifically, fail[0]=-1,
 * fail[i]<=fail[i-1]+1.
 *
 * str = "ababa" --> fail = [-1 0 0 1 2 3]
 *
 * ATTENTION: fail array has a length of str.length()+1 instead of str.length().
 */
vector<int> kmp_build(const string& str) {
  int len = str.length();
  vector<int> fail(len + 1, 0);
  fail[0] = -1;
  for (int i = 1, j; i <= len; ++i) {
    for (j = fail[i - 1]; ~j && str[i - 1] != str[j]; j = fail[j])
      ;
    fail[i] = j + 1;
  }
  return fail;
}

/**
 * If you simply want to run KMP algorithm, just invoke this function.
 *
 * ATTENTION: match array has a length of text.length()+1 instead of
 * text.length().
 */
vector<int> kmp(const string& text, const string& pattern) {
  vector<int> fail = kmp_build(pattern);
  int len = text.length();
  vector<int> match(len + 1, 0);
  for (int i = 1, j; i <= len; ++i) {
    for (j = match[i - 1]; ~j && text[i - 1] != pattern[j]; j = fail[j])
      ;
    match[i] = j + 1;
  }
  return match;
}