/*
 A brief explanation about use of a powerful library: orderd_set
 Reference link: http://codeforces.com/blog/entry/11080
 and a hash for the type pair 
 */
//compilar con g++ -std=c++11
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds;
typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;
/*
If we want to get map but not the set, as the second argument type must be used mapped type. Apparently,
 the tree supports the same operations as the set (at least I haven't any problems with them before), 
 but also there are two new features — it is find_by_order() and order_of_key(). 
 The first returns an iterator to the k-th largest element (counting from zero), the second — the number of items 
in a set that are strictly smaller than our item. Example of use:
* 
* */

//Compilar: g++ --std=c++11
struct Hash{
size_t operator()(const ii &a)const{
size_t s=hash<int>()(a.fst);
return hash<int>()(a.snd)+0x9e3779b9+(s<<6)+(s>>2);
}
size_t operator()(const vector<int> &v)const{
size_t s=0;
for(auto &e : v)
s ^= hash<int>()(e)+0x9e3779b9+(s<<6)+(s>>2);
return s;
}
};
unordered_set<ii, Hash> s;
unordered_map<ii, int, Hash> m;//map<key, value, hasher>
