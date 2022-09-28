#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> prefix_2d(const vector<vector<int>>& a)
{
  assert(a.size()>0&&a[0].size()>0);
  int n=a.size(),m=a[0].size();
  vector<vector<int>> pref(n,vector<int>(m,0));

  for(int i=0;i<n;++i)
  {
    for(int j=0;j<m;++j)
    {
      if(i==0&&j==0) pref[i][j]=a[i][j];
      else if(i==0) pref[i][j]=pref[i][j-1]+a[i][j];
      else if(j==0) pref[i][j]=pref[i-1][j]+a[i][j];
      else pref[i][j]=pref[i-1][j]+pref[i][j-1]-pref[i-1][j-1]+a[i][j];
    }
  }

  return pref;
}

int sum_subrect(const vector<vector<int>>& pref,int lx,int rx,int ly,int ry)
{
  return pref[rx][ry]+pref[lx-1][ly-1]-pref[lx-1][ry]-pref[rx][ly-1];
}