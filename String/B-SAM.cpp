#include<bits/stdc++.h>
using namespace std;

/**
 * SAM (Suffix AutoMaton)
 * 
 * The suffix automaton is a type of automaton that constructs all suffices of a certain string.
 * 
 * It's well-known for being capable to access all substrings indirectly.
 */
struct SAM
{
  vector<int> mp[26],fa;
  //ed:end-state ct:state counter (all starts from 1)
  int ed=1,ct=1;
  vector<int> len;
  
  int n;

  SAM(int _n):
    //generally SAM related
    n(_n),len(3*_n,0),fa(3*_n,0),
    //problem-specific
    siz(3*_n,0),v(3*_n,0),x(3*_n,0),al(3*_n,0)
  {
    for(int k=0;k<26;++k) mp[k].resize(3*_n);
  }

  //ATTENTION: off must be base-1.
  void insert(const char* str,int off)
  {
    //c: newly added character
    int c=str[off]-'a';
    int p=ed;
    //add a new node representing str[1:off]
    siz[ed=++ct]=1,len[ed]=off;
    //for all p from old-ed to 1, if there is no mp[c][p], then assign it to new-ed
    for(;p&&mp[c][p]==0;p=fa[p]) mp[c][p]=ed;
    //case 1: if all p does not have mp[c][p], then just link ed to 1.
    if(p==0) return void(fa[ed]=1);

    //case 2/3: there exists a p that has mp[c][p]=q.
    int q=mp[c][p];
    //if q is exactly behind p, then link ed to q.
    if(len[p]+1==len[q]) return void(fa[ed]=q);

    //case 3: we have to create another duplicate node of q. (except fa/len)
    len[++ct]=len[p]+1;
    for(int i=0;i<26;++i) mp[i][ct]=mp[i][q];
    //update suffix links
    fa[ct]=fa[q],fa[q]=ct,fa[ed]=ct;
    //continue linking until mp[c][i]!=q
    for(int i=p;mp[c][i]==q;i=fa[i]) mp[c][i]=ct;
  }

  /**
   * Example.
   * 
   * For all substring T of S, let the time of existence in S of T to be f(T).
   * Figure out A = max(f(T)*len(T)) for all f(T)>1.
   */
  //problem-specific
  int cnt=0;
  vector<int> v,x,al,siz;
  long long res=0;
  void add(int u,int V){ 
    v[++cnt]=V,x[cnt]=al[u],al[u]=cnt; 
  }
  void buildtree()
  {
    for(int i=2;i<=ct;++i) add(fa[i],i);
  }
  void dfs(int u)
  {
    for(int i=al[u];i;i=x[i]) dfs(v[i]),siz[u]+=siz[v[i]];
    if(siz[u]!=1) res=max(res,1ll*siz[u]*len[u]);
  }
};

int main()
{
  string S;cin>>S;
  SAM sam(S.length()+3);
  const char* _s=S.data()-1;
  for(int i=0,_i=S.length();i<_i;++i) sam.insert(_s,i+1);
  sam.buildtree();
  sam.dfs(1);
  cout<<sam.res<<endl;
  return 0;
}