#include<bits/stdc++.h>
using namespace std;

/**
 * Manacher Algorithm
 * 
 * O(n) algorithm to calculate the longest palindrome.
 * 
 * The function manacher() needs S to be base-0.
 */
int manacher(const char* S,int n)
{
  assert((S!=nullptr)&&(n>0));
  int k1,k2,ans=INT_MIN;
  vector<int> d1(n),d2(n);
  int l1=0,r1=-1,l2=0,r2=-1;
  for(int i=0;i<n;++i)
  {
    k1=(i>r1)?1:min(d1[l1+r1-i],r1-i+1);
    k2=(i>r2)?0:min(d2[l2+r2-i+1],r2-i+1);

    while(i-k1>=0&&i+k1<n&&S[i-k1]==S[i+k1]) k1++;
    while(i-k2-1>=0&&i+k2<n&&S[i-k2-1]==S[i+k2]) k2++;

    d1[i]=k1--;d2[i]=k2--;

    if(i+k1>r1) l1=i-k1,r1=i+k1;
    if(i+k2>r2) l2=i-k2-1,r2=i+k2;
    ans=max(ans,max(r1-l1+1,r2-l2+1));
  }
  return ans;
}

int main()
{
  string S;cin>>S;
  cout<<manacher(S.data(),S.length())<<endl;
  return 0;
}