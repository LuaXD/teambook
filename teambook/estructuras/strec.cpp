//inclusive segment tree [L,R] 
int T[4 * N];
void init(int node = 1,int l = 0,int r = n - 1){
	if(l == r)T[node] = v[l];
	else{
		int mid = (l + r) >> 1;
		init(2 * node,l,mid);
		init(2 * node + 1,mid + 1,r);
		T[node] = op(T[2 * node],T[2 * node + 1]);
	}
}
void update(int pos,int val,int node = 1,int l = 0,int r = n - 1){
	if(r < pos || l > pos)return;
	if(l == r)T[node] = val;
	else{
		int mid = (l + r) >> 1;
		update(pos,val,2 * node,l,mid);
		update(pos,val,2 * node + 1,mid + 1,r);
		T[node] = op(T[2 * node],T[2 * node + 1]);
	}
}
int query(int x,int y,int node = 1,int l = 0,int r = n - 1){
	if(r < x || l > y)return NEUTRO;
	if(x <= l && r <= y)return T[node];
	else{
		int mid = (l + r) >> 1;
		return op(query(x,y,2 * node,l,mid),query(x,y,2 * node + 1,mid + 1,r));
	}
}
