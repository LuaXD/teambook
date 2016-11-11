//TRIDIAGONAL SOLVER
// solve ai*x_i-1 + bi*x_i + ci*x_i+1 = d_i
//a_0 = 0 c_n-1 = 0
/*
  b :subdiagonal
  a :diagonal  
  c :super diagonal
 */
//the answer is in D
#define MAXN 5000
long double A[MAXN], B[MAXN], C[MAXN], D[MAXN], X[MAXN];
void solve(int n) {
    C[0] /= B[0]; D[0] /= B[0];
    for(int i = 1; i < n - 1;i++) C[i] /= B[i] - A[i]*C[i-1];
    for(int i = 1; i < n;i++)D[i] = (D[i] - A[i] * D[i-1]) / (B[i] - A[i] * C[i-1]);
    X[n-1] = D[n-1];
    for (int i = n-2; i>=0; i--) X[i] = D[i] - C[i] * X[i+1]; 
}
