#include <bits/extc++.h>
using namespace std;

// better QoL string
using fstring = __gnu_cxx::crope;
void test_crope() {
  fstring a = "aabb";
  cout << a.substr(0, 2) << endl;
  cout << a.c_str() << endl;  // might lead to memleaks
  a.delete_c_str();
  // insert text before pos 2
  a.insert(2, "22333");
  cout << a << endl;
  // erase[3,3+2)
  a.erase(3, 2);
  cout << a << endl;
}