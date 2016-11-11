void shift(int id){
	if(lazy[id])
		lazy[2 * is] = lazy[2 * id + 1] = lazy[id];
	lazy[id] = 0;
}
//color > 1, por que se usa el 0 para decir que no hay lazy
void upd(int x,int y,int color, int id = 0,int l = 0,int r = n){//painting the interval [x,y) whith color "color"
	if(x >= r or l >= y)	return ;
	if(x <= l && r <= y){
		lazy[id] = color;
		return ;
	}
	int mid = (l+r)/2;
	shift(id);
	upd(x, y, color, 2 * id, l, mid);
	upd(x, y, color, 2*id+1, mid, r);
}

set <int> se;
void cnt(int id = 1,int l = 0,int r = n){
	if(lazy[id]){
		se.insert(lazy[id]);
		return ; // there is no need to see the children, because all the interval is from the same color
	}
	if(r - l < 2)	return ;
	int mid = (l+r)/2;
	cnt(2 * id, l, mid);
	cnt(2*id+1, mid, r);
}