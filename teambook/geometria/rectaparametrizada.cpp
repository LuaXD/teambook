bool between(fraction a, fraction b, fraction c) {
  return a <= c && c <= b;
}
struct segment {
  fraction pendiente, ordenada;
  fraction A, B;
  segment(fraction p, fraction ord, fraction a, fraction b) {
    pendiente = p;
    ordenada = ord;
    A = a;
    B = b;
  }
  bool read() {//retorna true si no se vertical
    fraction a, b, c, d;//(a,b) (c,d)
    a.read();
    b.read();
    c.read();
    d.read();
    if (a == c) {//vertical
      A = min(b, d);
      B = max(b, d);
      ordenada = a;
      return false;
    }
    A = min(a, c);
    B = max(a, c);
    pendiente = (d - b) / (c - a);
    ordenada = b - (pendiente * a);
    return true;
  }
  bool same_line(const segment &other) const {
    return (pendiente == other.pendiente) && (ordenada == other.ordenada);
  }
  bool intersect(const segment &other) const {
    if (!same_line(other)) return false;
    return between(A, B, other.A) || between(A, B, other.B);
  }
  void merge(const segment &other) const {
    A = min(A, other.A);
    B = min(B, other.B);
  }
  bool operator < (const segment &other) const {
    if (A == other.A)
      return B < other.B;
    return A < other.A;
  }
  string to_string() {
    stringstream ss;
    ss << "(" << A.to_string() << ", " << B.to_string() << ")";
    return ss.str();
  }
};
int main() {
  int n; cin >> n;  
  vector<segment> verticales;
  vector<segment> normal;
  forn (i, n) {
    segment x;
    if (x.read()) {
      normal.pb(x);
    } else {
      verticales.pb(x);
    }
  }
  return 0;
}