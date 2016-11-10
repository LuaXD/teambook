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
vector<int> manacher(const string &_s) {
  int n = _s.size();
  string s(2 * n + 3, '#');
  s[0] = '%', s[s.size() - 1] = '$';//no deben estar en la cadena
  for (int i = 0; i < n; i++)
    s[(i + 1) * 2] = _s[i];

  n = s.size();
  vector<int> P(n, 0);
  int C = 0, R = 0;
  for (int i = 1; i < n - 1; i++) {
    int j = C - (i - C);
    if (R > i)
      P[i] = min(R - i, P[j]);
    while (s[i + 1 + P[i]] == s[i - 1 - P[i]])
      P[i]++;
    if (i + P[i] > R) {
      C = i;
      R = i + P[i];
    }
  }
  return P;
}
bool is_pal(const vector<int> &mnch_vec, int i, int j) {//[i, j] - i<=j
  int len = j - i + 1;
  i = (i + 1) * 2;//idx to manacher vec idx
  j = (j + 1) * 2;
  int mid = (i + j) / 2;
  return mnch_vec[mid] >= len;
}
int main() {
  string s;
  cin >> s;
  vector<int> mnch_vec= manacher(s);
  if (is_pal(mnch_vec, 2, 7)) {
    //la subcadena desde la posicion 2 a la 7 es palindrome
  }
  return 0;
}

