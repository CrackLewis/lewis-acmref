#include<bits/stdc++.h>
using namespace std;

/**
 * Trie maps are specifically designed to solve character mapping problems in trie.
 * All you need is a struct with static member chr_tot and function map(char).
 */
struct LwrcLatinTrieMap
{
  const static int chr_tot=26;
  static int map(char ch){ return int(ch-'a'); }
};
struct FullAscMap
{
  const static int chr_tot=128;
  static int map(char ch){ return (ch+256)%128; }
};

/**
 * Trie 
 * 
 * Also known as dictionary tree.
 */
template<class _Mp=LwrcLatinTrieMap>
struct Trie
{
  //You might need to decrease sz_incr if testcases are too much.(e.g. T>=1e4)
  //For fewer cases you can enlarge the value to boost efficiency.
  const static int sz_incr=20;

  vector<int> tr[_Mp::chr_tot];
  int n,ncnt;

  Trie(int n=0):n(n),ncnt(0),exists(n,0)
  {
    for(int i=0;i<_Mp::chr_tot;++i) tr[i].resize(n,-1);
    newnode();
  }

  int newnode()
  {
    if(ncnt>=n)
    {
      int _n=n+sz_incr;
      for(int i=0;i<_Mp::chr_tot;++i) tr[i].resize(_n);
      exists.resize(_n);
      n=_n;
    }
    ncnt++;
    return ncnt-1;
  }

  void insert(const string& s)
  {
    int cur=0,mp,nd;
    for(auto& ch:s)
    {
      if(tr[mp=_Mp::map(ch)][cur]==0)
      //it looks weird but no tr[mp][cur] can be 0 ;)
      {
        nd=newnode();
        tr[mp][cur]=nd;
      }
      cur=tr[mp][cur];
      exists[cur]++;
    }
  }

  /**
   * Trie has multiple usages than simply finding a string.
   * 
   * Here shows a sample using exist array to count existences of a string in the string set.
   */
  vector<int> exists;
  int find(const string& s)
  {
    int cur=0,mp;
    for(auto& ch:s)
    {
      if(tr[mp=_Mp::map(ch)][cur]==0) return 0;
      cur=tr[mp][cur];
    }
    return exists[cur];
  }
};