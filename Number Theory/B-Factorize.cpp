#include<bits/stdc++.h>
using namespace std;

/**
 * Integer Factorization Algorithm - Pollard-Rho
 * 
 * The common factorization method which is O(sqrt(n)):
 * Iterate all i in [1,sqrt(n)] to test if n%i==0.
 * If we have a prime table the method complexity is O(sqrt(n)/ln(n)).
 * 
 * When n goes too large it is impossible to absolutely confirm all factorials.
 * But we can still perform PRIME TESTS to get ALMOST all of them.
 * 
 * The core idea of factorization is *** Pollard-Rho *** algorithm.
 * Pollard-rho algorithm tries to find a factor of x.
 * Specifically, it tries to find a k in the rho-loop of [0,x-1] which satisfies gcd(k,x)>1, which indicates that x%k==0.
 * 
 * Miller-Rabin method is the PRIMALITY TEST method used in Pollard-rho.
 * It relies on the fermat theory and quad-detection theory to ensure correctness.
 */

using LL=long long int;
LL gcd(LL a,LL b){ return b?gcd(b,a%b):a; }
/**
 * Why using a lot of __int128_t here?
 * Because we want to do quickpow on LL type, which needs int128 for temporary storage.
 * (Guisucheng is shit)
 */
LL ksm(LL a,LL b,LL mod)
{
  LL res=1ll;
  while(b)
  {
    if(b&1) res=((__int128_t)res*a)%mod;
    b>>=1,a=((__int128_t)a*a)%mod;
  }
  return res;
}
//Miller-Rabin test
LL miller_rabin(LL x,LL b)
{
  LL k=x-1;
  while(k)
  {
    LL cur=ksm(b,k,x);
    //violates the quad-detection
    if(cur!=1&&cur!=x-1) return false;
    if((k&1)==1||cur==x-1) return true;
    k>>=1;
  }
  return true;
}
//primality test
bool isprime(LL x)
{
  //the only failed case in our approach is 46856248255981. 
  //so it's specially listed here.
  if(x==46856248255981ll||x<2) return false;
  if(x==2||x==3||x==7||x==61||x==24251) return true;
  return miller_rabin(x,2)&&miller_rabin(x,61);
}
//transform used in pollard-rho
LL f(LL x,LL c,LL n){ return ((__int128_t)x*x+c)%n; }
//the god rolls a dice
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
//pollard_rho(x): returns a factor of x
LL pollard_rho(LL x)
{
  LL s=0,t=0,c=1ll*rnd()%(x-1)+1;
  int stp=0,goal=1;
  LL val=1;
  for(goal=1;goal;goal<<=1,s=t,val=1)
  {
    for(stp=1;stp<=goal;++stp)
    {
      t=f(t,c,x);
      val=(__int128_t)val*abs(t-s)%x;
      if((stp%127)==0)
      {
        LL d=gcd(val,x);
        if(d>1) return d;
      }
    }
    LL d=gcd(val,x);
    if(d>1) return d;
  }
  return x;
}

/**
 * Example.
 * 
 * factorize() generates a list of factors of x.
 */
map<LL,int> factors;
void factorize(LL x,LL pw=1)
{
  if(x<2) return;
  if(isprime(x))
  {
    factors[x]+=pw;
    return;
  }
  LL p=x,ppw=0;
  while(p>=x) p=pollard_rho(x);
  while((x%p)==0) x/=p,ppw++;
  //split factors
  factorize(x,pw),factorize(p,pw*ppw);
}

int main()
{
  LL x;
  int _;cin>>_;while(_--)
  {
    cin>>x;
    factors.clear();
    factorize(x);
    cout<<x<<'=';
    bool frstar=false;
    for(auto& pr:factors)
    {
      if(frstar) cout<<'*';
      else frstar=true;
      cout<<pr.first;
      if(pr.second>1) cout<<'^'<<pr.second;
    }
    cout<<endl;
  }
  return 0;
}