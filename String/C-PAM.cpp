#include<bits/stdc++.h>
using namespace std;

/**
 * 
 * PAM (Palindrome Automaton)
 * 
 * Constructs a tree containing all distinct palindromes of a sequence.
 * 
 * PAM has two roots representing two sets of palindromes with even and odd lengths.
 * 
 */
struct PAM
{
  //sz: palindrome counter
  //tot: total characters.
  int sz=-1,tot=0,last=0;
  int n;
  vector<int> cnt,ch[26],len,fail;
  string S;

  PAM(int _n):
    //general
    n(_n),cnt(_n),len(_n),fail(_n),S(_n,'\0'),
    //prob-specific
    num(_n)
    {
      for(int i=0;i<26;++i) ch[i].resize(_n);
      clear();
    }
  
  //new node
  int node(int l)
  {
    sz++;
    for(int i=0;i<26;++i) ch[i][sz]=0;
    len[sz]=l;
    fail[sz]=cnt[sz]=0;
    return sz;
  }

  void clear()
  {
    sz=-1,last=0;
    S[tot=0]='$';
    //two root nodes: 0,-1
    node(0),node(-1);
    //fail[0]=1,fail[1]=0 links to each other.
    fail[0]=1;
  }

  int getfail(int x)
  {
    while(S[tot-len[x]-1]!=S[tot]) x=fail[x];
    return x;
  }

  void insert(char c)
  {
    S[++tot]=c;
    int now=getfail(last);
    if(!ch[c-'a'][now])
    {
      int x=node(len[now]+2);
      fail[x]=ch[c-'a'][getfail(fail[now])];
      ch[c-'a'][now]=x;
      //prob-spec
      num[x]=num[fail[x]]+1;
    }
    last=ch[c-'a'][now];
    lst=num[last]; //prob-spec
    cnt[last]++;
  }

  /**
   * Example.
   * Figure out the number of distinct palindromic substrings in string s.
   */
  int solve1()
  {
    function<int(int)> dfs=[&](int x)
    {
      int sz=1;
      for(int i=0;i<26;++i)
        if(ch[i][x]) sz+=dfs(ch[i][x]);
      return sz;
    };
    //all nodes excluding 2 roots
    return dfs(0)+dfs(1)-2;
  }

  vector<int> num;
  int lst;
  /**
   * Example.
   * Calculate the number of palindromes ending in each position of the string.
   */
  vector<int> solve2()
  {
    return num;
  }
};

//Luogu P5496
int main()
{
  string s;cin>>s;
  PAM pam(s.length()+3);
  int lst=0;
  for(int i=0,_i=s.length();i<_i;++i)
  {
    s[i]=(s[i]-97+lst)%26+97;
    pam.insert(s[i]);
    cout<<(lst=pam.lst)<<' ';
  }
  cout<<endl;
  return 0;
}