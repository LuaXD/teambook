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
const int maxn = 800 + 10;
vector<vector<int> > g;
bool mark[maxn * maxn];
int match[maxn * maxn];
bool dfs(int left) {
  if (mark[left]) return false;
  mark[left] = true;
  for (int right: g[left])
    if (match[right] == -1 || dfs(match[right])){
      match[right] = left;
      match[left] = right;
      return true;
    }
  return false;
}
int MCBM(int n, int k) {
  fill(match, match + n + k, -1);
  while (true)  {
    bool fnd = false;
    fill(mark, mark + n + k, false);
    forn (i, n)
      if (match[i] == -1 && !mark[i])
        fnd |= dfs(i);
    if (!fnd)
      break;
  }
  int ans = 0;
  forn (i, n)
    if (match[i] != -1)
      ans++;
  /*forn (i, n)
    if (match[i] != -1)
      printf("%d - %d\n", i, match[i] - n);*/
  return ans;
}
void mvc_dfs(int u) {
  if (mark[u]) return;
  mark[u] = 1;
  for (int v: g[u])
    if (!mark[v]) {
      mark[v] = 1;
      mvc_dfs(match[v]);
    }
}
vector<int> min_vertex_cover(int n, int k) {
  vector<int> ans;
  int N = n + k;
  fill(mark, mark + N, 0);
  for (int u = 0; u < n; u++)
    if (!mark[u] && match[u] == -1)
      mvc_dfs(u);
  //Todos los de la izquierda(que esten en el MCBM) que no hayan sido marcados
  for (int i = 0; i < n; i++)
    if (match[i] != -1 && !mark[i])
      ans.pb(i);
  //Todos los de la derecha(que esten en el MCBM) que hayan sido marcados
  for (int i = n; i < N; i++)
    if (match[i] != -1 && mark[i])
      ans.pb(i);
  return ans;
}
int rows, cols;
char mapa[maxn][maxn];
int rowsID[maxn][maxn];
int colsID[maxn][maxn];
int n_rows;
int n_cols;
vector<pair<int , pair<int,int> > > rows_movs, cols_movs;
int main() {
  while (scanf("%d %d", &rows, &cols) == 2) {
    forn (i, rows)
      scanf("%s", mapa[i]);
    //forn (i, rows)
    //  cout << mapa[i] << endl;
    forn (i, rows) forn (j, cols)
      rowsID[i][j] = colsID[i][j] = -1;
    rows_movs.clear();
    cols_movs.clear();
    int NEXT_FREE_ID_ROWS = 0, NEXT_FREE_ID_COLS = 0;
    forn (row, rows) {
      int col = 0;
      while (col < cols) {
        while (col < cols && mapa[row][col] == '.')
          col++;
        bool next = false;
        int pre = col;
        while (col < cols && mapa[row][col] == '*') {
          rowsID[row][col] = NEXT_FREE_ID_ROWS;
          col++;
          next = true;
        }
        if (next) {
          rows_movs.emplace_back(row, mp(pre, col - 1));
          NEXT_FREE_ID_ROWS++;
        }
      }
    }
    forn (col, cols) {
      int row = 0;
      while (row < rows) {
        while (row < rows && mapa[row][col] == '.')
          row++;
        bool next = false;
        int pre = row;
        while (row < rows && mapa[row][col] == '*') {
          colsID[row][col] = NEXT_FREE_ID_COLS;
          row++;
          next = true;
        }
        if (next) {
          cols_movs.emplace_back(col, mp(pre, row - 1));
          NEXT_FREE_ID_COLS++;
        }
      }
    }
    n_rows = NEXT_FREE_ID_ROWS;
    n_cols = NEXT_FREE_ID_COLS;
    /*DBG(n_rows);
    DBG(n_cols);
    forn (i, rows) {
      forn (j, cols)
        printf("%3d ", rowsID[i][j]);
      printf("\n");
    }
    printf("\n");
    forn (i, rows) {
      forn (j, cols)
        printf("%3d ", colsID[i][j]);
      printf("\n");
    }
    */

    (vector<vector<int>>(n_rows + n_cols, vector<int>())).swap(g);
    forn (row, rows) forn (col, cols) 
      if (mapa[row][col] == '*')
        g[rowsID[row][col]].push_back(n_rows + colsID[row][col]);


    int ans = MCBM(n_rows, n_cols);
    vector<int> mvc = min_vertex_cover(n_rows, n_cols);


    assert(sz(mvc) == ans);
    printf("%d\n", ans);
    for (int e: mvc) {
      if (e < n_rows) {
        printf("hline %d %d %d\n", rows_movs[e].first + 1, rows_movs[e].second.first + 1, rows_movs[e].second.second + 1);
      } else {
        printf("vline %d %d %d\n", cols_movs[e - n_rows].first + 1, cols_movs[e - n_rows].second.first + 1, cols_movs[e - n_rows].second.second + 1);
      }
    }
  }
  return 0;
}

