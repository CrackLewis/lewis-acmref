#include <bits/extc++.h>
using namespace std;

/**
 * Debug function
 *
 * This function outputs variable numbers of parameters into std::cout.
 * If you want to disable the debug output, just comment the lines in
 * debug(a,oth...).
 */

void debug() { cout << endl; }
template <class T1, class... T2>
void debug(T1 a, T2... oth) {
  cout << a << ' ';
  debug(oth...);
}