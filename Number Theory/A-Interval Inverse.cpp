#include<bits/stdc++.h>
using namespace std;

/**
 * Interval inverse algorithm
 * 
 * Single point inverse cost O(k) time. (k=log mod)
 * Interval inverse can solve all inverse in [1,n] at O(1) in average.
 * 
 * ATTENTION: returning sequence is base-1.
 */
vector<int> q_inv(int n,int mod)
{
  vector<int> ret(n+1);
  ret[1]=1;
  for(int i=2;i<=n;++i)
    ret[i]=(long long)(mod-mod/i)*ret[mod%i]%mod;
  return ret;
}

int main()
{
  int n,p; cin>>n>>p;
  auto inv=q_inv(n,p);
  copy(inv.begin()+1,inv.end(),ostream_iterator<int>(cout,"\n"));
  return 0;
}