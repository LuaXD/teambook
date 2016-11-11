/*Dada una string S contar la cantidad de pares de subcadenas S[i..j] S[a..b], tales que las primeras k letras de ambas sean iguales */
//r[i] = pos;
//h[i] = lcp;
number C2[maxn];
int main(){
  forn (i, maxn)
    C2[i] = ((i * (i - 1LL)) / 2LL) % mod;
  int k;
  cin >> s >> k;
  s.push_back('$');
  n = s.size();
  suff_arr();
  lcp();
  number ans = 0;
  number acu = 0;
  n--;
  for (int i = 1; i <= n; i++) {
    int tam = (n + 1) - r[i];
    number extra = tam - k;
    if (tam >= (k + 1)) {
      ans += C2[extra];
      ans %= mod;
      ans += ((acu * extra) % mod);
      ans %= mod;
    }
    if (h[i] >= k)
      acu += extra;
    else
      acu = 0;
  }
  cout << ans << "\n";
  return 0;
}
