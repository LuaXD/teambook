#include <iostream>
#include <climits>
#include <vector>
#include <limits>
#include <cmath>
using namespace std;

typedef double DOUBLE;
typedef vector<DOUBLE> VD;
typedef vector<VD> VVD;
typedef vector<int> VI;

const DOUBLE EPS = 1e-9;

struct solver{
	int m,n;
	VI B,N;
	VVD D;

	solver(const VVD &A,const VD &b, const VD &c):
		m(b.size()), n(c.size()), N(n + 1), B(m), D(m + 2, VD(n + 2)){
			for(int i = 0; i < m;i++)
				for(int j = 0; j < n;j++)
					D[i][j] = A[i][j];
			for(int i  = 0; i < m;i++)
				{B[i] = n + i;D[i][n] = -1, D[i][n + 1] = b[i];}
			for(int i = 0; i < n;i++){ N[i] = i; D[m][i] = -c[i]; }
			N[n] = -1; D[m + 1][n] = 1;
		}
		void pivot(int r,int s){
			double inv = 1.0 / D[r][s];
			for(int i = 0; i < m + 2;i++)
				if(i != r)
					for(int j = 0; j < n + 2;j++)
						if(j != s)
							D[i][j] -= D[r][j] * D[i][s] * inv;
			for(int j = 0; j < n + 2;j++)
				if(j != s)
					D[r][j] *= inv;
			for(int i = 0; i < m + 2;i++)
				if(i != r)
					D[i][s] *= -inv;
			D[r][s] = inv;
			swap(B[r],N[s]);
		}
		bool simplex(int phase){
			int x = phase == 1? m + 1:m;
			while(true){
				int s = -1;
				for(int j = 0; j <= n;j++){
					if(phase == 2 && N[j] == -1)continue;
					if(s == -1 || D[x][j] < D[x][s] || D[x][j] == D[x][s] && N[j] < N[s])s = j;
				}
				if(D[x][s] > -EPS)return true;
				int r = -1;
				
				for(int i = 0; i < m;i++){
					if(D[i][s] < EPS)continue;
					if(r == -1 || 
						D[i][n + 1] / D[i][s] < D[r][n + 1] / D[r][s] || (D[i][n + 1] / D[i][s]) == (D[r][n + 1] / D[r][s]) && B[i] < B[r])
						r = i;
				}
				if(r == -1)return false;
				pivot(r,s);
			}
		}
		int solve(VD &x){
			int r = 0;
			for(int i = 1; i < m;i++)
				if(D[i][n + 1] < D[r][n + 1]) r = i;
			if(D[r][n + 1] < -EPS){
				pivot(r,n);
				if(!simplex(1) || D[m + 1][n + 1] < -EPS)return -1;
				for(int i = 0; i < m;i++)
					if(B[i] == -1){
						int s = -1;
						for(int j = 0; j <= n;j++)
							if(s == -1 || D[i][j] < D[i][s] || D[i][j] == D[i][s] && N[j] < N[s]) s = j;
						pivot(i,s);
					}
			}
			if(!simplex(2))return 1;
			x = VD(n);
			for(int i = 0; i < m;i++)
				if(B[i] < n)
					x[B[i]] = D[i][n + 1];
			return 0;
		}
};

int main() {
	cout.precision(16);
	int n, m;
	cin >> n >> m;
	VVD A(n, VD(m));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
		cin >> A[i][j];
		}
	}
	VD b(n);
	for(int i = 0; i < n;i++)cin >> b[i];
	VD c(m);
	for(int i = 0; i < m;i++)cin >> c[i];
	solver sol(A,b,c);
	VD x;
	int ans = sol.solve(x);
	if(ans == -1){
		cout << "No solution\n";
	}
	if(ans == 0){
		cout << "Bounded solution\n";
		for(int i = 0; i < x.size();i++)cout <<fixed<< x[i] << " ";
	}
	if(ans == 1){
		cout << "Infinity\n";
	}
	return 0;
}
