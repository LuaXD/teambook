#include <bits/stdc++.h>
using namespace std;
#define forn(i,n) for(int i = 0; i < (n); i++)
const int INF = INT_MAX/2;

//Para non-increasing, cambiar comparaciones y revisar busq binaria
//Given an array, paint it in the least number of colors so that each color turns to a non-increasing subsequence.
//Solution:Min number of colors=Length of the longest increasing subsequence

// Las lineas marcadas con // Camino no son necesarias si no se desea reconstruir el camino.
#define MAXN 1000000
int v[MAXN]; // INPUT del algoritmo.
int mv[MAXN];
int mi[MAXN] ,p[MAXN]; // Camino
int l[MAXN]; // Aca apareceria la maxima subsecuencia creciente(los indices)
int lis(int n) {
	forn(i,n) mv[i] = INF;
	forn(i,n) mi[i] = -1; // Camino
	forn(i,n) p [i] = -1; // Camino
	mv[0] = -INF;
	int res = 0;
	forn(i,n)	{
		// Con upper_bound es maxima subsecuencia no decreciente.
		// Con lower_bound es maxima subsecuencia creciente.
		int me = upper_bound(mv,mv+n,v[i]) - mv;
		p[i] = mi[me-1]; // Camino
		mv[me] = v[i];
		mi[me] = i; // Camino
		if (me > res) res = me;
	}
	for(int a = mi[res], i = res - 1;a != -1; a = p[a], i--) // Camino
		l[i] = a; // Indices: poniendo l[i] = v[a] quedan los valores.
	return res;
}

int main() {
	int n;
	cin >> n;
	forn (i, n)
		cin >> v[i];
	int tam = lis(n);
	cout << tam << endl;
	forn (i, tam)
		cout << l[i] << " ";
	cout << endl;
	forn (i, tam)
		cout << v[l[i]] << " ";
	cout << endl;
	return 0;
}
