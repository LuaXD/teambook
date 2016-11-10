/*
 A brief explanation about use of a powerful library: orderd_set
 Reference link: http://codeforces.com/blog/entry/11080
 and a hash for the type pair 
 */

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
/*
If we want to get map but not the set, as the second argument type must be used mapped type. Apparently,
 the tree supports the same operations as the set (at least I haven't any problems with them before), 
 but also there are two new features - it is find_by_order() and order_of_key(). 
 The first returns an iterator to the k-th largest element (counting from zero), the second - the number of items 
in a set that are strictly smaller than our item. Example of use:
* 
* */

