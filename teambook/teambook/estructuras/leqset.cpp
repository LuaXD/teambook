//insersion y consulta de cuantos <= en log n
struct leqset {
  int maxl; vector<int> c;
  int pref(int n, int l) { return (n>>(maxl-l))|(1<<l); }
  void ini(int ml) { maxl=ml; c=vector<int>(1<<(maxl+1)); }
  //inserta c copias de e, si c es negativo saca c copias
  void insert(int e, int q=1) { forn(l,maxl+1) c[pref(e,l)]+=q; }
  int leq(int e) {
    int r=0,a=1;
    forn(i,maxl) {
      a<<=1; int b=(e>>maxl-i-1)&1;
      if (b) r+=c[a]; a|=b;
    } return r + c[a]; //sin el c[a] da los estrictamente menores
  }
  int size() { return c[1]; }
  int count(int e) { return c[e|(1<<maxl)]; }
};
