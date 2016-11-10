/*Segment Tree modificar un rango, acceder a una posicion
	solo sirve cuando la operacion que realizamos es conmutativa
	por ejemplo la suma, pero no funciona con la asignacion
*/
//adiciona value al rango [l, r)
void modify(int l, int r, int value) {// rango [l, r)
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l&1) t[l++] += value;
    if (r&1) t[--r] += value;
  }
}
//acceder a la posicion
int query(int p) {
  int res = 0;
  for (p += n; p > 0; p >>= 1) res += t[p];
  return res;
}
//Si necesitamos actualizar todo lo podemos hacer en O(n)
//Y luego acceder a las hojas en O(1)
void push() {
  for (int i = 1; i < n; ++i) {
    t[i<<1] += t[i];
    t[i<<1|1] += t[i];
    t[i] = 0;
  }
}