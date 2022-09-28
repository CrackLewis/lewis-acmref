#include<bits/stdc++.h>
using namespace std;

/**
 * Segment Tree
 * 
 * 
 */
using LL=long long int;

struct segtree
{
#define lc (x<<1)
#define rc (x<<1|1)
#define mid ((l+r)>>1)

  vector<LL> sum,add,mul;
  int n; LL p;

  segtree(int n):sum((n<<2)+4),add((n<<2)+4),mul((n<<2)+4),n(n) {}

  void up(int x,int l,int r)
  {
    sum[x]=(sum[lc]+sum[rc])%p;
  }

  void down(int x,int l,int r)
  {
    mul[lc]=(mul[lc]*mul[x])%p;
    mul[rc]=(mul[rc]*mul[x])%p;
    add[lc]=(add[lc]*mul[x])%p;
    add[rc]=(add[rc]*mul[x])%p;
    sum[lc]=(sum[lc]*mul[x])%p;
    sum[rc]=(sum[rc]*mul[x])%p;
    mul[x]=1;

    add[lc]=(add[lc]+add[x])%p;
    add[rc]=(add[rc]+add[x])%p;
    sum[lc]=(sum[lc]+(mid-l+1)*add[x])%p;
    sum[rc]=(sum[rc]+(r-mid)*add[x])%p;
    add[x]=0;
  }

  void build(int x,int l,int r,LL* a)
  {
    mul[x]=1,add[x]=0;
    if(l>=r) return void(sum[x]=a[l]%p);
    build(lc,l,mid,a),build(rc,mid+1,r,a);
    up(x,l,r);
  }

  void addv(int x,int l,int r,int ll,int rr,int d)
  {
    if(ll<=l&&r<=rr)
    {
      sum[x]=(sum[x]+1ll*(r-l+1)*d)%p;
      add[x]=(add[x]+d)%p;
      return;
    }
    if(mul[x]!=1||add[x]!=0) down(x,l,r);
    if(ll<=mid) addv(lc,l,mid,ll,rr,d);
    if(mid+1<=rr) addv(rc,mid+1,r,ll,rr,d);
    up(x,l,r);
  }

  void mulv(int x,int l,int r,int ll,int rr,int d)
  {
    if(ll<=l&&r<=rr)
    {
      sum[x]=(sum[x]*d)%p;
      mul[x]=(mul[x]*d)%p;
      add[x]=(add[x]*d)%p;
      return;
    }
    if(mul[x]!=1||add[x]!=0) down(x,l,r);
    if(ll<=mid) mulv(lc,l,mid,ll,rr,d);
    if(mid+1<=rr) mulv(rc,mid+1,r,ll,rr,d);
    up(x,l,r);
  }

  LL query(int x,int l,int r,int ll,int rr)
  {
    LL res=0ll;
    if(ll<=l&&r<=rr) return sum[x]%p;
    if(add[x]!=0||mul[x]!=1) down(x,l,r);
    if(ll<=mid) res+=query(lc,l,mid,ll,rr);
    if(mid+1<=rr) res+=query(rc,mid+1,r,ll,rr);
    return res%p;
  }
#undef lc
#undef rc
#undef mid
};

int main()
{
  int n,m,p;cin>>n>>m>>p;
  vector<LL> a(n+1);
  for(int i=1;i<=n;++i) cin>>a[i];
  segtree seg(n);
  seg.p=p;
  seg.build(1,1,n,a.data());

  int op,x,y,k;
  while(m--)
  {
    cin>>op;
    if(op==1) cin>>x>>y>>k,seg.mulv(1,1,n,x,y,k);
    else if(op==2) cin>>x>>y>>k,seg.addv(1,1,n,x,y,k);
    else if(op==3) cin>>x>>y,cout<<seg.query(1,1,n,x,y)<<endl;
  }
  return 0;
}