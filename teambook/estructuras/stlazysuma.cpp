//Todo es [l, r)
void build(int id = 1,int l = 0,int r = n){
	if(r - l < 2){	//	l + 1 == r
		s[id] = a[l];
		return ;
	}
	int mid = (l+r)/2;
	build(id * 2, l, mid);
	build(id * 2 + 1, mid, r);
	s[id] = s[id * 2] + s[id * 2 + 1];
}
//aqui poner los arrays lazy and id
void upd(int id,int l,int r,int x){//	increase all members in this interval by x
	lazy[id] += x;
	s[id] += (r - l) * x;
}
//A function to pass the update information to its children :
void shift(int id,int l,int r){//pass update information to the children
	int mid = (l+r)/2;
	upd(id * 2, l, mid, lazy[id]);
	upd(id * 2 + 1, mid, r, lazy[id]);
	lazy[id] = 0;// passing is done
}
//A function to perform increase queries :
void increase(int x,int y,int v,int id = 1,int l = 0,int r = n){
	if(x >= r or l >= y)	return ;
	if(x <= l && r <= y){
		upd(id, l, r, v);
		return ;
	}
	shift(id, l, r);
	int mid = (l+r)/2;
	increase(x, y, v, id * 2, l, mid);
	increase(x, y, v, id*2+1, mid, r);
	s[id] = s[id * 2] + s[id * 2 + 1];
}
//(We should call increase(l r x))
int sum(int x,int y,int id = 1,int l = 0,int r = n){
	if(x >= r or l >= y)	return 0;
	if(x <= l && r <= y)	return s[id];
	shift(id, l, r);
	int mid = (l+r)/2;
	return sum(x, y, id * 2, l, mid) +
	       sum(x, y, id * 2 + 1, mid, r);
}