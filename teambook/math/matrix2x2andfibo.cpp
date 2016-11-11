	typedef number tipo;

tipo mod;
struct M22 {         //|a b|
	tipo a, b, c, d; //|c d|
	M22 operator * (const M22 &p) const {
		return (M22){(a*p.a+b*p.c) % mod, (a*p.b+b*p.d) % mod, (c*p.a+d*p.c) % mod, (c*p.b+d*p.d) % mod};
	}
};
M22 operator ^ (const M22 &p, tipo n) {
	if(!n) return (M22){1, 0, 0, 1};//matriz identidad
	M22 q = p ^ (n/2); q = q * q;
	return (n % 2)? p * q : q;
}
//devuelve el n-esimo fibonacci (index 0)
//f0 = fibo(0), f1 = fibo(1);
tipo fibo(tipo n, tipo f0, tipo f1) {
	M22 mat=(M22){0, 1, 1, 1}^n;
	return (mat.a*f0 + mat.b*f1) % mod;
}
