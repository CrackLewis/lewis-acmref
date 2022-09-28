/**
 * Number Theory Basics
 * 
 * - gcd (greatest common divisor)
 * - exgcd (extended GCD)
 * - ksm/gsc (quickpower/slow(but-robust) mul)
 * - m_inv (multiplicative inverse)
 * - frac_rd (fraction reduction: 3/6 => 1/2)
 */

#include<bits/stdc++.h>
using namespace std;

using LL=long long int;
const LL MOD998=998244353;
const LL MOD107=1000000007;
// ATTENTION: You need to modify MOD to problem specific values.
const LL MOD=MOD998;

LL gcd(LL a,LL b)
{
  return b?gcd(b,a%b):a;
}

LL exgcd(LL a,LL b,LL& x,LL& y)
{
  if(!b)
  {
    x=1,y=0;
    return a;
  }
  LL ret=exgcd(b,a%b,y,x);
  y-=(a/b)*x;
  return ret;
}

//returns (a**b)%MOD, a,b in INT32
LL ksm(LL a,LL b,LL mod=MOD)
{
  LL ret=1ll;
  while(b)
  {
    if(b&1) ret=(ret*a)%mod;
    b>>=1,a=(a*a)%mod;
  }
  return ret;
}

//returns (a*b)%MOD, a,b in INT64
LL gsc(LL a,LL b,LL mod=MOD)
{
  LL ret=0ll;
  while(b)
  {
    if(b&1) ret=(ret+a)%mod;
    a=(a+a)%mod,b>>=1;
  }
  return ret;
}

//returns mult-inverse of x
//using fermat little theorem: a^(p-1)===1 (mod p)
LL m_inv(LL x,LL mod=MOD)
{
  return ksm(x,mod-2)%mod;
}

//fraction reduction
void frac_rd(LL& dend,LL& dor)
{
  assert(dor!=0);
  if(dend==0) dor=1;
  int f=1;
  if(dend<0) dend=-dend,f=-f;
  if(dor<0) dor=-dor,f=-f;
  LL _gcd=gcd(dend,dor);
  dend/=_gcd,dor/=_gcd;
  dend*=f;
}