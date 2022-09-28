#include <bits/stdc++.h>
using namespace std;

/**
 * Trie maps are specifically designed to solve character mapping problems in
 * trie. All you need is a struct with static member chr_tot and function
 * map(char).
 */
struct LwrcLatinTrieMap {
  const static int chr_tot = 26;
  static int map(char ch) { return int(ch - 'a'); }
};
struct FullAscMap {
  const static int chr_tot = 128;
  static int map(char ch) { return (ch + 256) % 128; }
};

/**
 * Aho-Corasick Automaton (a.k.a. AC Automaton)
 *
 * AC automaton is a combination of Trie and KMP fail function.
 * It maintains a trie of all pattern strings where every node has a fail
 * pointer pointing to next matching node position.
 *
 * Each node in the automaton indicates a prefix of a pattern string.
 * Fail pointer of each node points to the longest suffix which exists in the
 * automaton. If the suffix does not exist, fail pointer points to the root.
 *
 * To use the automaton:
 * - AhoCorasick<> aut(1000010);
 * - for(auto pattern:patterns) aut.insert(pattern);
 * - aut.build_fail();
 * - aut.query(text);
 *
 * *** ATTENTION ***
 * This AC automaton cannot modify its node size dynamically.
 * Refer to Trie for dynamic size policy.
 */
template <class _Mp = LwrcLatinTrieMap>
struct AhoCorasick {
  vector<int> tr[_Mp::chr_tot];
  int n, tot;
  vector<int> fail;

  AhoCorasick(int _n) : n(_n), fail(_n, 0), tot(1), e(_n, 0) {
    assert((_n >= 1) && "invalid automaton size");
    for (int i = 0; i < _Mp::chr_tot; ++i) tr[i].resize(_n, 0);
  }

  int newnode() { return tot++; }

  // e:number of duplicate strings
  vector<int> e;
  void insert(const string& str) {
    int cur = 0, mp;
    for (auto& ch : str) {
      if (!tr[mp = _Mp::map(ch)][cur]) tr[mp][cur] = newnode();
      cur = tr[mp][cur];
    }
    e[cur]++;
  }

  void build_fail() {
    queue<int> Q;
    for (int i = 0; i < _Mp::chr_tot; ++i)
      if (tr[i][0]) Q.push(tr[i][0]);
    while (Q.size()) {
      int u = Q.front();
      Q.pop();
      for (int i = 0; i < _Mp::chr_tot; ++i) {
        // if next position exists, then set fail
        if (tr[i][u]) fail[tr[i][u]] = tr[i][fail[u]], Q.push(tr[i][u]);
        // else modify the trie structure
        else
          tr[i][u] = tr[i][fail[u]];
      }
    }
  }

  // query(string&) returns the number of patterns existing for at least once in
  // the text string.
  int query(const string& text) {
    // do a backup so e isn't sabotaged
    vector<int> _e = e;
    int cur = 0, res = 0, mp;
    for (auto& ch : text) {
      cur = tr[mp = _Mp::map(ch)][cur];
      for (int j = cur; j && ~_e[j]; j = fail[j]) res += _e[j], _e[j] = -1;
    }
    return res;
  }
};