//extension c++ header
#include<bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;

//better QoL map
template<class A,class B>
using slower_map = map<A,B>;
template<class A,class B>
using slow_map = unordered_map<A,B>;
template<class A,class B>
using fast_map = __gnu_pbds::cc_hash_table<A,B>;
template<class A,class B>
using faster_map = __gnu_pbds::gp_hash_table<A,B>;

//balanced tree tests
//Luogu P3369 - Balanced Tree
using LL=long long int;
void test_pbds_tree()
{
  __gnu_pbds::tree<LL,null_type,less<LL>,rb_tree_tag,tree_order_statistics_node_update> tr;
  int n; cin>>n;
  int opt; LL k,ans;
  for(int i=1;i<=n;++i)
  {
    cin>>opt>>k;
    //1 - insert k
    if(opt==1) tr.insert((k<<20)+i);
    //2 - delete k
    if(opt==2) tr.erase(tr.lower_bound(k<<20));
    //3 - query rank of k (elements lower than k + 1)
    if(opt==3) cout<<(tr.order_of_key(k<<20)+1)<<endl;
    //4 - query the number ranking k-th of all
    if(opt==4) ans=*tr.find_by_order(k-1),cout<<(ans>>20)<<endl;
    //5 - query the previous element of k
    if(opt==5) ans=*--tr.lower_bound(k<<20),cout<<(ans>>20)<<endl;
    //6 - query the successing element of k
    if(opt==6) ans=*tr.upper_bound((k<<20)+n),cout<<(ans>>20)<<endl;
  }
}