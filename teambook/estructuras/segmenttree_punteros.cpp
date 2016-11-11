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

typedef int tipo;
tipo PONGA_AQUI_EL_NEUTRO = INT_MAX;

/*La creacion y las queries son [0, n)
[cerrado, abierto)
Por alguna razon el destructor hace que se borre todo
inmediatamente despues de que termina el constructor*/
const int maxn = 1000000;
tipo v[maxn];

const tipo NEUTRO = PONGA_AQUI_EL_NEUTRO;
tipo oper(tipo a, tipo b) {
  return min(a, b);
}
struct segment_tree {
  segment_tree *L, *R;
  int l, r;
  tipo value;
  segment_tree(): L(nullptr), R(nullptr), value(NEUTRO) {}
  segment_tree(int _l, int _r) : l(_l), r(_r) {
    if (l + 1 == r) {
      value = v[l];
    } else {
      int mid = (l + r) >> 1;
      L = new segment_tree(l, mid);
      R = new segment_tree(mid, r);
      value = oper(L->value, R->value);
    }
  }
  //~segment_tree() {delete L; delete R;}//NO PONER!!! ERROR!!!
  void update(int pos, int val) {
    if (r <= pos || l > pos) return;
    if (l + 1 == r) {
      v[pos] = value = val;
    } else {
      L->update(pos, val);
      R->update(pos, val);
      value = oper(L->value, R->value);
    }
  }
  tipo query(int a, int b) {
    if (a <= l && r <= b) return value;
    if (l >= b || r <= a) return NEUTRO;
    return oper(L->query(a, b), R->query(a, b));
  }
} tree;

void dfs(segment_tree *u, string espacio = "") {
  if (u == nullptr) return;
  cout << espacio << "(" << u->l << ", " << u->r << ") -> "  << u->value << endl;
  dfs(u->L, espacio + " ");
  dfs(u->R, espacio + " ");
}
int main() {
  int n = 1000;
  forn (i, n)
    v[i] = rand() % 1007;
  tree = segment_tree(0, n);
  //dfs(&tree);
  cout << "ST creado" << endl;
  int cntqueries = 0;
  for (int i = 0; i < n; i++) {
    int sum = INT_MAX;
    for (int j = i; j < n; j++) {
      sum = min(sum, v[j]);
      int stresp = tree.query(i, j + 1);
      if (sum != stresp) {
        DBG(sum);
        DBG(stresp);
        assert(false);
      }
      cntqueries++;
    }
  }
  DBG(cntqueries);
  cout << "funciono" << endl;
  return 0;
}

