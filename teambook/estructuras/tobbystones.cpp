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
const int PAINT = 0, FLIP = 1, REVERSE = 2;
struct rope {
  typedef struct _node {
    int value, y, cnt;
    int negros;
    bool rev;
    bool lazy_flip;
    int lazy_pintar;
    _node *l, *r;
    _node(int _value) : value(_value), y((rand() << 16) ^ rand()), cnt(1), l(nullptr), r(nullptr) {
      negros = _value;
      rev = false;
      lazy_flip = false;
      lazy_pintar = -1;
    }
    ~_node() {delete l; delete r;}
    void recalc() {
      cnt = 1;
      negros = value;
      if (l) cnt += l->cnt, negros += l->negros;
      if (r) cnt += r->cnt, negros += r->negros;
    }
    void push_lazy(int type, int param = -1) {
      if (type == PAINT) {
        rev = false;
        lazy_flip = false;
        lazy_pintar = param;
        negros = param * cnt;
      }
      if (type == FLIP) {
        if (lazy_pintar != -1) {
          assert(rev == false && lazy_flip == false);
          lazy_pintar = (1 - lazy_pintar);
          negros = lazy_pintar * cnt;
        } else {
          lazy_flip ^= true;
          negros = cnt - negros;
        }
      }
      if (type == REVERSE) {
        if (lazy_pintar == -1) {
          rev ^= true;
        }
      }
    }
    void verify() {
      bool op1 = (lazy_pintar != -1);
      bool op2 = (rev || lazy_flip);
      //solo puede pasar uno de los 2 casos, o ninguno esta activado o solo uno de los dos
      assert((!op1 and !op2) or (op1 xor op2));
    }
    string to_string() {
      stringstream ss;
      ss << "value=" << value << ", negros=" << negros << ", cnt="<< cnt << "("<<rev<< "," << lazy_pintar<<","<< lazy_flip << ")";
      return ss.str();
    }
  } *node;
  rope(): root(nullptr) {}
  ~rope() {delete root;}
  node root;
  void push(node &t) {
    if (t == nullptr) return;
    bool op1 = ((t->lazy_pintar) != -1);
    bool op2 = ((t->rev) || (t->lazy_flip));
    //solo puede pasar uno de los 2 casos, o ninguno esta activado o solo uno de los dos
    assert((!op1 and !op2) or (op1 xor op2));
    if (op1) {
      t->value = t->lazy_pintar;
      if (t->l) t->l->push_lazy(PAINT, t->lazy_pintar);
      if (t->r) t->r->push_lazy(PAINT, t->lazy_pintar);
      t->lazy_pintar = -1;
    }
    if (op2) {//no importa el orden en que se aplique estos 2
      //reverse
      if (t->rev) {
        swap(t->l, t->r);
        t->rev = false;
        if (t->l) t->l->push_lazy(REVERSE);
        if (t->r) t->r->push_lazy(REVERSE);
      }
      //invertir colores
      if (t->lazy_flip) {
        t->value = 1 - (t->value);
        t->lazy_flip = false;
        if (t->l) t->l->push_lazy(FLIP);
        if (t->r) t->r->push_lazy(FLIP);
      }
    }
  }
  void split(node t, int x, node &L, node &R) {
    push(t);
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
  node merge(node L, node R) {
    push(L); push(R);
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
  void insert(int pos, int value) {
    node L, R;
    split(root, pos, L, R);//en R esta pos
    root = merge(merge(L, new _node(value)), R);
  }
  int cnt(node t) {
    return t ? t->cnt : 0;
  }
  int size() {
    return cnt(root);
  }
  void reverse(int i, int j) {
    node L, m, R;
    split(root, i, L, R);
    split(R, j - i + 1, m, R);
    m->push_lazy(REVERSE);
    root = merge(merge(L, m), R);
  }
  void flip(int i, int j) {
    node L, m, R;
    split(root, i, L, R);
    split(R, j - i + 1, m, R);
    m->push_lazy(FLIP);
    root = merge(merge(L, m), R);
  }
  void pintar(int i, int j, int color) {
    node L, m, R;
    split(root, i, L, R);
    split(R, j - i + 1, m, R);
    m->push_lazy(PAINT, color);
    root = merge(merge(L, m), R);
  }
  void query(int i, int j) {
    node L, m, R;
    split(root, i, L, R);
    split(R, j - i + 1, m, R);
    int negros = m->negros;
    int blancos = m->cnt - negros;
    printf("%d %d\n", negros, blancos);
    root = merge(merge(L, m), R);
  }
  void print(node &t, string spacio, char lado = ' ') {
    if (t == nullptr) return;
    cout << spacio << lado <<" -> " << (t->to_string()) << endl;
    print(t->l, spacio + "\t", 'L');
    print(t->r, spacio + "\t", 'R');
  }
  void print() {
    print(root, "");
  }
};
int main() {
  //srand(time(nullptr));
  int n, m;
  while (scanf("%d %d", &n, &m) == 2) {
    rope tree;
    forn (i, n)
      tree.insert(sz(tree), 0);
    while (m--) {
      int q, i, j;
      scanf("%d %d %d", &q, &i, &j);
      if (q == 0)
        tree.query(i, j);
      if (q == 1)
        tree.reverse(i, j);
      if (q == 2)
        tree.flip(i, j);
      if (q == 3) {
        int color;
        scanf("%d", &color);
        tree.pintar(i, j, 1 - color);
      }
    }
  }
  return 0;
}

