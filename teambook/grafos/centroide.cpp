
const int MAXN = 100010;
vector<int> g[MAXN];
int ID[MAXN];
int cnt[MAXN];
int contar(int u, int parent) {
  if (ID[u] != -1) return cnt[u] = 0;
  cnt[u] = 1;
  for (int v: g[u])
    if (v != parent)
      cnt[u] += contar(v, u);
  return cnt[u];
}
int get_centroid(int u, int parent, int size) {
  for (int v: g[u])
    if (v != parent)
      if (cnt[v] > (size / 2))
        return get_centroid(v, u, size);
  return u;
} 
void dfs(int u, int id) {
  contar(u, -1);
  int centroid = get_centroid(u, -1, cnt[u]);
  ID[centroid] = id;
  for (int v: g[centroid])
    if (ID[v] == -1)
      dfs(v, id + 1);
}

int main() {
  memset(ID, -1, sizeof(ID));//No olvidar esta linea
  //el arbol es conexo
  //iniciar con "dfs(nodoqueexiste, 0)"
  dfs(0, 0);
  /*
    Esta implementación halla el centroide y elimina el centroide
    y halla el centroide de los subarboles(recursivamente)
    Complejidad: O(N Log(N))
    Si solo se quiere el centroide del arbol
    solo llamar a la funcion "get_centroid" una sola vez
    "get_centroid(nodoqueexiste, -1, contar(u, -1))"
    No olvidar el "contar(u, -1)" para preprocesar tamaños
    
   */
  return 0;
}
