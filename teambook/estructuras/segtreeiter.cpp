//Segment tree iterative [l,r)
int T[2 * N];
void init(){
	for(int i = n; i < 2 * n;i++)T[i] = val[i];
	for(int i = n - 1; i >= 1; i--)T[i] = op(T[i << 1],T[i << 1 | 1]);
}
int op(int a,int b){
	//an asociative function
	return a + b;
}
void update(int pos,int u){
	pos += n;
	for(pos >>= 1; pos >= 1; pos >>= 1)T[pos] = op(T[pos << 1],T[pos << 1 | 1]);
}

int query(int l,int r){
	l += n, r += n;
	int ans = NEUTRO;
	while(l  < r){
		if(l & 1)ans = op(ans,T[l++]);
		if(r & 1)ans = op(ans,T[--r]);
		l >>= 1,r >>= 1;
	}
	return ans;
}
