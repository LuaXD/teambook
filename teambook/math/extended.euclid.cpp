number ext_gcd(number a, number b, number &x, number &y){
  if(b == 0) {
    x = 1; y = 0; return a;
  }
  number g = ext_gcd(b,a % b,y,x);
  y -= a / b * x;
  return g;
}
pair<number, number> solve(number a, number b, number c, number n, number m, number g, number tk) {
  pair<number, number> ans(LLONG_MAX, LLONG_MAX);
  for (number k = tk - 3; k < tk + 3; k++) {
    number x = (n * c) / g + (b * k) / g;
    number y = (m * c) / g - (a * k) / g;
    if (x >= 1 && y >= 1)
      ans = min(ans, mp(x, y));
  }
  return ans;
}
int main() {
  //Encuentra a y b de a*x + b*x = c
  //tal que a > 0 && b > 0 y minimiza (a, b)
  number a, b, c;
  scanf("%lld %lld %lld", &a, &b, &c);
  number n, m;
  number g = ext_gcd(a, b, n, m);
  number L = (g - n * c) / b, R = (m * c - g) / a;
  auto ans =min(solve(a, b, c, n, m, g, L),solve(a, b, c, n, m, g, R));
  printf("%lld %lld\n", ans.first, ans.second);
  return 0;
}