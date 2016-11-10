#include <bits/stdc++.h>

using namespace std;
typedef long long int tipo;


const int maxn = 500010;
int n;

tipo v[maxn];//vector principal

tipo lazy[maxn];
pair<tipo, tipo> t[maxn];//para poder reordenar los elementos

int SQRT;
int N;//nro. de buckets

//Recalcula y aplica el lazy al bucket con indice idx
//guarda la informacion necesaria del bucket en otros vectores
//podria ser la suma del bucket, o el min/max del bucket
void recalc(int idx) {
	int a = idx * SQRT, b = min(n, (idx + 1) * SQRT);
	for (int i = a; i < b; i++) {
		v[i] += lazy[idx];
		t[i] = make_pair(v[i], i);
	}
	lazy[idx] = 0;
	sort(t + a, t + b);
}

//adiciona delta a todos los elementos
//en el intervalo cerrado [a, b]
void add(int a, int b, tipo delta) {
	int idx_a = a / SQRT, idx_b = b / SQRT;
	if (idx_a == idx_b) {
		for (int i = a; i <= b; i++)
			v[i] += delta;
		recalc(idx_a);
	} else {
		//head
		for (int i = a, lim = min(n, (idx_a + 1) * SQRT); i < lim; i++)
			v[i] += delta;
		recalc(idx_a);//OJO puede ser necesario
		//body
		for (int i = idx_a + 1; i < idx_b; i++)
			lazy[i] += delta;
		//tail
		for (int i = idx_b * SQRT; i <= b; i++)
			v[i] += delta;
		recalc(idx_b);//OJO puede ser necesario
	}
}

//tambien podria ser en un rango como en el add
tipo query(tipo val) {
	tipo ans = 0;
	//recorro todos los buckets
	for (int idx = 0; idx < N; idx++) {
		int a = idx * SQRT, b = min(n, (idx + 1) * SQRT);
		//... hacer algo ...
	}
	return ans;
}
int main() {
	//leer n, q y los elementos de v

	SQRT = (int)sqrt(n) + 1;
	N = (n + SQRT - 1) / SQRT;//nro. de buckets
	//construir cada bucket
	for (int idx = 0; idx < N; idx++)
		recalc(idx);
	
	//resto del programa
	return 0;
}
