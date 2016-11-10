#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
const int N = 300;
typedef vector<double> col;
typedef vector<double> row;
typedef vector<row>Matrix;
col solution;
int main(){
	Matrix M;
	M.resize(300);
	solution.resize(300);
	for(int i = 0; i < 30;i++)M[i].resize(30);
	int n;
	cin >> n;
	for(int i = 0; i < n;i++)
		for(int j = 0; j <= n;j++)
			cin >> M[i][j];
			
	for(int j = 0; j < n - 1;j++){
		int l =j;
		for(int i = j + 1; i < n;i++){
			if(fabs(M[i][j]) > fabs(M[l][j]))l = i;
		}
		for(int k = j; k <= n;k++){
			swap(M[j][k],M[l][k]);
		}
		for(int i = j + 1; i < n;i++)
			for(int k = n; k >= j;k--)
				M[i][k] -= M[j][k] * M[i][j] / M[j][j];
	}
	double t = 0;
	for(int j = n - 1; j >= 0; j--){
		t = 0.0;
		for(int k = j + 1; k < n;k++)t += M[j][k] * solution[k];
		solution[j] = (M[j][n] - t) / M[j][j];
	}
	cout.precision(4);
	for(int i = 0; i < n;i++)cout<<fixed << solution[i] << " ";
	return 0;
}
