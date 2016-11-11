vector<tipo> tree;
int maxn;
void init(int n) {
	tree = vector<tipo>(n, 0);
	maxn = n;
}
void add(int i, tipo k) { //i valid [1, n)
  for(; i < maxn; i += i&-i ) tree[i] += k;
}

tipo get(int i){//returns sum [1, i]
  tipo s = 0;
  for(; i > 0; i-=i&-i) s+=tree[i];
  return s;
}