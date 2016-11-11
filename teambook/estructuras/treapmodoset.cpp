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
struct treap {
  typedef struct _node {
    int x, y, cnt;
    _node *l, *r;
    _node(int _x) : x(_x), y((rand() << 16) ^ rand()), cnt(1), l(nullptr), r(nullptr) {}
    ~_node() {delete l; delete r;}
    void recalc() {
      cnt = 1;
      if (l) cnt += l->cnt;
      if (r) cnt += r->cnt;
    }
  } *node;
  treap(): root(nullptr) {}
  ~treap() {delete root;}
  node root;
  /*Divide el arbol que tiene como raiz a "t", guarda en 
    L todos los nodos con key menor o igual a "x"
    R todos los nodos con key mayor estricto a x
    t es destruido/modificado
   */
  void split(node t, int x, node &L, node &R) {
    if (t == nullptr) {L = R = nullptr; return;}
    if (t->x <= x) {
      split(t->r, x, t->r, R);
      L = t;
    } else {
      split(t->l, x, L, t->l);
      R = t;
    }
    t->recalc();
  }
  /*Une los dos nodos L y R en un solo arbol y los devuelve.
    L y R son modificados
   */
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
  /*Inserta un solo nodo con key igual a "x"*/
  void insert(int x) {
    //verificar que no se inserten elementos repetidos
    //pueden ocasionar que ya no cumplan la propiedad de BST
    //pueden haber keys iguales a izquierda y derecha
    node L, R;
    split(root, x, L, R);
    root = merge(merge(L, new _node(x)), R);
  }
  /*Borra todos los nodos con key igual a "x"
    No pasa nada si no hay nodos con key igual a "x"*/
  void erase(int x) {
    node L, m, R;
    split(root, x, L, R);
    split(L, x - 1, L, m);
    root = merge(L, R);
  }
  int count(int x) {
    node L, m, R;
    split(root, x, L, R);
    split(L, x - 1, L, m);
    int ans = cnt(m);
    root = merge(merge(L, m), R);
    return ans;
  }
  /*Borra un nodo con key igual a "x"
    No sucede nada si no hay nodo con ese key*/
  void erase_one(int x) {
    node L, m, R;
    split(root, x, L, R);
    split(L, x - 1, L, m);
    if (m)
      m = merge(m->l, m->r);
    root = merge(merge(L, m), R);
  }
  /*k-esimo indexado desde 0
     devuelve INT_MAX si no hay k-esimo*/
  int kthElement(int k) {
    node cur = root;
    while (cur != nullptr) {
      int sizeLeft = cnt(cur->l);
      if (sizeLeft == k)
        return cur->x;
      cur = sizeLeft > k ? cur->l : cur->r;
      if (sizeLeft < k)
        k -= (sizeLeft + 1);
    }
    return INT_MAX;
  }
  /*Numero de elementos con keys menores a "x"*/
  int less(int x) {
    node cur = root;
    int ans = 0;
    while (cur != nullptr) {
      if (cur->x >= x) {
        cur = cur->l;
      } else {
        ans += cnt(cur->l) + 1;
        cur = cur->r;
      }
    }
    return ans;
  }
  int cnt(node t) const {
    return t ? t->cnt : 0;
  }
  int size() const {
    return cnt(root);
  }
/*//from e-maxx.ru son mas rapidos(no x mucho) pero menos entendibles
//solo borra un elemento
  void erase(node &t, int x) {
    if (t->x == x)
      t = merge(t->l, t->r);
    else
      erase(x < t->x?t->l:t->r, x);
    if (t)
      t->recalc();
  }
  void erase_one(int x) {erase(root, x);}
  void insert(node &t, node it) {
    if (t == nullptr)
      t = it;
    else if (it->y > t->y)
      split(t, it->x, it->l, it->r), t = it;
    else
      insert(it->x < t->x? t->l: t->r, it);
    t->recalc();
  }
  void insert(int x) {insert(root, new _node(x));}*/
};
 /*
TODO: - Agregar lower_bound con mejor constante que el count(se puede hacer iterativo)
   */
int buscar_nuevo(const multiset<int> &s) {
  while (true) {
    int x = rand();
    if (!s.count(x))
      return x;
  }
  assert(false);
}
int existente(const multiset<int> &s) {
  while (true) {
    auto it = s.lower_bound(rand());
    if (it != s.end())
      return *it;
  }
  assert(false);
}
int main() {
  srand(time(nullptr));
  treap t;
  multiset<int> s;
  const int n = 10000000;
  forn (q, 2 * n) {
    int tipo = rand() % 3;
    if (tipo == 0) {//insert
      int subtipo = rand() % 2;
      if (subtipo == 0 && sz(s) > 0) {//uno que ya existia
        int elem = existente(s);
        t.insert(elem);
        s.insert(elem);
      } else {//uno nuevo
        int elem = buscar_nuevo(s);
        t.insert(elem);
        s.insert(elem);
      }
    } else if (tipo == 1) {//query
      int subtipo = rand() % 2;
      if (subtipo == 0 && sz(s) > 0) {//uno que ya existia
        int elem = existente(s);
        assert((int)t.count(elem) == (int)s.count(elem));
      } else {//uno que no exisita 
        int elem = buscar_nuevo(s);
        assert((int)t.count(elem) == (int)s.count(elem));
      }
    } else {//erase, borra todos los elementos, no solo uno !!!
      int subtipo = rand() % 2;
      if (subtipo == 0 && sz(s) > 0) {//uno que si existia
        int elem = existente(s);
        t.erase(elem);
        s.erase(elem);
      } else {//uno nuevo
        int elem = buscar_nuevo(s);
        t.erase(elem);
        s.erase(elem);
      }
    }
    assert(sz(s) == sz(t));
  }
  vector<int> elems(all(s));
  elems.resize(unique(all(elems)) - elems.begin());
  for (int e: elems)
    assert((int)s.count(e) == (int)t.count(e));
  DBG(sz(t));
  return 0;
}

