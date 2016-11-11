/*
 A brief explanation about use of a powerful library: orderd_set
 Reference link: http://codeforces.com/blog/entry/11080
 and a hash for the type pair 
 */
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds;
/*typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
If we want to get map but not the set, as the second argument type must be used mapped type. Apparently,  the tree supports the same operations as the set (at least I haven't any problems with them before),  but also there are two new features - it is find_by_order() and order_of_key(). 
The first returns an iterator to the k-th largest element (counting from zero), the second - the number of items 
in a set that are strictly smaller than our item. Example of use:*/
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
int main(){
  ordered_set<int>  s;
  s.insert(1); 
  s.insert(3);
  cout << *s.find_by_order(0) << endl; // print the 0-th smallest number in s(0-based)
  cout << s.order_of_key(2) << endl; // the number of elements in the s less than 2
  //find_by_order(i) devuelve iterador al i-esimo elemento
  //order_of_key(k): devuelve la pos del lower bound de k
  //Ej: 12, 100, 505, 1000, 10000.
  //order_of_key(10) == 0, order_of_key(100) == 1,
  //order_of_key(707) == 3, order_of_key(9999999) == 5
  return 0;
}


