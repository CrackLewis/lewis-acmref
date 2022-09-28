#include<bits/stdc++.h>
using namespace std;

/**
 * Fast Fourier Transform (FFT)
 * Number Theory Transform (NTT)
 * 
 * two most common polynomial transformation method.
 */

// ============ FFT ============

const double PI=acos(-1.0);
struct Complex
{
  double r,i;
  Complex(double _r=0,double _i=0):r(_r),i(_i){}
};
Complex operator+(const Complex& a,const Complex& b){ return Complex(a.r+b.r,a.i+b.i); }
Complex operator-(const Complex& a,const Complex& b){ return Complex(a.r-b.r,a.i-b.i); }
Complex operator*(const Complex& a,const Complex& b){ return Complex(a.r*b.r-a.i*b.i,a.r*b.i+a.i*b.r); }

/**
 * FFT(int limit,Complex* a,int type,const vector<int>& r)
 * 
 * args:
 * - limit: the length of sequence a, must be 2^k pattern
 * - a:     sequence to be transformed
 * - type:  transformation type
 *   type=1: coefficient to value
 *   type=-1: value to coefficient
 * - r:     rule sequence of re-sort
 * 
 * Luogu P3803 - 2.85s 72.55MB
 */
void FFT(int limit,Complex* a,int type,const vector<int>& r)
{
  //re-sort the array into iteration sequence
  for(int i=0;i<limit;++i)
    if(i<r[i]) swap(a[i],a[r[i]]);
  //iterate merging period length from 1 to limit/2
  for(int mid=1;mid<limit;mid<<=1)
  {
    Complex Wn(cos(PI/mid), type*sin(PI/mid));//complex unit
    for(int R=mid<<1,j=0;j<limit;j+=R)//period [j,j+R)
    {
      Complex w(1,0);
      //iterate left half
      for(int k=0;k<mid;++k,w=w*Wn)
      {
        Complex x=a[j+k],y=w*a[j+mid+k];//butterfly effect lol
        a[j+k]=x+y;
        a[j+mid+k]=x-y;
      }
    }
  }
}

void FFT_demo()
{
  int n,m;
  cin>>n>>m;
  
  int limit=1,l=0;while(limit<=n+m) limit<<=1,l++;
  vector<int> r(limit);
  for(int i=0;i<limit;++i)
    r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
  
  Complex a[limit+1],b[limit+1];
  for(int i=0;i<=n;++i) cin>>a[i].r;
  for(int i=0;i<=m;++i) cin>>b[i].r;
  FFT(limit,a,1,r);
  FFT(limit,b,1,r);
  for(int i=0;i<=limit;++i)
    a[i]=a[i]*b[i];
  FFT(limit,a,-1,r);
  for(int i=0;i<=n+m;++i) cout<<(int)(a[i].r/limit+0.5)<<' ';
  cout<<endl;
}

// ============ NTT ============
using LL=long long int;
//NTT arguments. P must be the pattern r*2^k+1, where k must be greater than limit.
const LL P=998244353,G=3,Gi=332748118;
LL ksm(LL a,LL b,LL mod=P)
{
  LL ret=1ll;
  while(b)
  {
    if(b&1) ret=(ret*a)%mod;
    b>>=1,a=(a*a)%mod;
  }
  return ret;
}

/**
 * NTT(int limit,LL* a,int type,const vector<int>& r)
 * 
 * args:
 * - limit: the length of sequence a, must be 2^k pattern
 * - a:     sequence to be transformed
 * - type:  transformation type
 *   type=1: coefficient to value
 *   type=-1: value to coefficient
 * - r:     rule sequence of re-sort
 * 
 * Luogu P3803 - 1.89s 40.51MB
 */
void NTT(int limit,LL* a,int type,const vector<int>& r)
{
  for(int i=0;i<limit;++i)
    if(i<r[i]) swap(a[i],a[r[i]]); //re-sort
  //accumulate length
  for(int mid=1;mid<limit;mid<<=1)
  {
    LL Wn=ksm(type==1?G:Gi, (P-1)/(mid<<1));//number theory unit
    for(int j=0;j<limit;j+=(mid<<1))
    {
      LL w=1;
      for(int k=0;k<mid;++k,w=(w*Wn)%P)//iterate left half period
      {
        LL x=a[j+k],y=w*a[j+k+mid]%P;
        a[j+k]=(x+y)%P;
        a[j+k+mid]=(x-y+P)%P;
      }
    }
  }
}

void NTT_demo()
{
  int n,m; cin>>n>>m;
  int limit=1,l=0; while(limit<=n+m) limit<<=1,l++;
  vector<int> r(limit);
  for(int i=0;i<limit;++i)
    r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));

  vector<LL> a(limit+1),b(limit+1);
  for(int i=0;i<=n;++i) cin>>a[i];
  for(int i=0;i<=m;++i) cin>>b[i];
  NTT(limit,a.data(),1,r),NTT(limit,b.data(),1,r);
  for(int i=0;i<limit;++i) a[i]=(a[i]*b[i])%P;
  NTT(limit,a.data(),-1,r);
  LL inv=ksm(limit,P-2)%P;
  for(int i=0;i<=n+m;++i)
    cout<<(a[i]*inv)%P<<' ';
  cout<<endl;
}