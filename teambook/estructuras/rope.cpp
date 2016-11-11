#include <bits/stdc++.h>

using namespace std;

#ifdef ACMTUYO
struct RTC{~RTC(){cerr << "Time: " << clock() * 1.0 / CLOCKS_PER_SEC <<" seconds\n";}} runtimecount;
#define DBG(X) cerr << #X << " = " << X << '\n';
#else
struct RTC{};
#define DBG(X)
#endif

#define fast_io() ios_base::sync_with_stdio(false)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define eb emplace_back
#define sz(x) ((int)(x).size())
#define all(c) (c).begin(),(c).end()
#define forn(i, n) for (int i = 0; i < (n); i++)
typedef long long int number;
struct rope {
  typedef struct _node {
    int value, y, cnt;
    _node *l, *r;
    _node(int _value) : value(_value), y((rand() << 16) ^ rand()), cnt(1), l(nullptr), r(nullptr) {}
    ~_node() {delete l; delete r;}
    void recalc() {
      cnt = 1;
      if (l) cnt += l->cnt;
      if (r) cnt += r->cnt;
    }
  } *node;
  rope(): root(nullptr) {}
  ~rope() {delete root;}
  node root;
  /*Divide el arbol que tiene como raiz a "t", guarda en 
   L los primeros "x" elementos del array
   R el primer elemento de R es el elemento en posicion x(indexado desde 0) del array
   t es destruido/modificado
   L = [0, x)
   R = [x, n) */
  void split(node t, int x, node &L, node &R) {
    if (t == nullptr) {L = R = nullptr; return;}
    int curIndex = cnt(t->l) + 1;
    if (curIndex <= x) {
      split(t->r, x - curIndex, t->r, R);
      L = t;
    } else {
      split(t->l, x, L, t->l);
      R = t;
    }
    t->recalc();
  }
  /* Une los dos nodos L y R en un solo arbol y los devuelve.
     L y R son modificados */
  node merge(node L, node R) {
    if (L == nullptr) return R;
    if (R == nullptr) return L;
    if (L->y > R->y) {
      L->r = merge(L->r, R);
      L->recalc();
      return L;
    } else {
      R->l = merge(L, R->l);
      R->recalc();
      return R;
    }
  }
  /*Inserta "value" en la posicion "pos"(indexado desde 0) recorre todos los elementos a la derecha desde la posicion pos*/
  void insert(int pos, int value) {
    node L, R;
    split(root, pos, L, R);//en R esta pos
    root = merge(merge(L, new _node(value)), R);
  }
  /*Borra el elemento en posicion pos*/
  void erase(int pos) {
    node L, m, R;
    split(root, pos, L, R);
    split(R, 1, m, R);
    root = merge(L, R);
  }
  int cnt(node t) const {
    return t ? t->cnt : 0;
  }
  int size() const {
    return cnt(root);
  }
};
int main() {srand(time(nullptr));return 0;}

