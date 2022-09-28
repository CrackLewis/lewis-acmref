#include<bits/stdc++.h>
using namespace std;

/**
 * Gauss-Jordan Elimination
 * 
 * Eliminate an (n * (n+1)) shaped matrix A to the following form:
 * - all A_{i,i} are non-zero.
 * - all A_{i,n+1} could be non-zero.
 * - all other elements are zero.
 * 
 * This algorithm is capable of solving multi-variable linear equation groups.
 * The function gauss(M) returns:
 * - 0 if eliminating attempt had failed.
 * - 1 if elimination was successful.
 */
int gauss(vector<vector<double>>& M)
{
  assert((M.size()>0)&&(M[0].size()==M.size()+1));
  int n=M.size();
  //iterate all columns except the last one
  for(int i=0;i<n;++i)
  {
    //pick the maximum of A[i...n,i]
    int maxrow=i;
    for(int j=i+1;j<n;++j)
    {
      if(fabs(M[j][i])>fabs(M[maxrow][i]))
        maxrow=j;
    }
    //swap the maxrow-th row with the i-th row
    for(int j=0;j<=n;++j)
      swap(M[i][j],M[maxrow][j]);
    //if the maximum is 0, it turns out that the entire row is 0, which is unsolvable.
    if(!M[i][i]) return 0;
    //iterate all rows and eliminate
    for(int j=0;j<n;++j)
    {
      if(j==i) continue;
      double temp=M[j][i]/M[i][i];
      for(int k=i;k<=n;++k)
        M[j][k]-=M[i][k]*temp;
    }
  }
  //regularize
  for(int i=0;i<n;++i)
    M[i][n]/=M[i][i],M[i][i]=1;
  return 1;
}

int main()
{
  int n;cin>>n;
  vector<vector<double>> a(n,vector<double>(n+1));
  //cout<<setprecision(2)<<fixed;
  for(int i=0;i<n;++i)
  {
    for(int j=0;j<=n;++j) cin>>a[i][j];
  }
  if(!gauss(a)) cout<<"No Solution"<<endl;
  else
  {
    for(int i=0;i<n;++i) cout<<a[i][n]<<endl;
  }
  return 0;
}