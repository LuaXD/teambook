typedef long long ll;
struct segmetree{
	int n;
	vector<ll>T;
	segmetree(){n = 0;}
	segmetree(int _){
		n = _;
		T.resize(2 * n + 1);
	}
	void rupdate(int pos,int value){
		pos += n;
		T[pos] = value;
		for(pos >>= 1; pos >= 1; pos >>= 1)
			T[pos] = T[pos << 1] + T[pos << 1 | 1];
	}
	void update(int pos,int value){
		pos += n;
		T[pos] += value;
		for(pos >>= 1; pos >= 1; pos >>= 1)
			T[pos] = T[pos << 1] + T[pos << 1 | 1];
	}
	int query(int l,int r){
		l += n;r+= n;
		int ans = 0;
		while(l < r){
			if(l & 1)ans += T[l++];
			if(r & 1)ans += T[--r];
			l >>= 1, r >>= 1;
		}
		return ans;
	}
};
struct st{
	int n;
	vector<segmetree>T;
	st(){}
	st(int _){
		n = _;
		for(int i = 0;i < 2 * n;i++){
			T.push_back(segmetree(n));
		}
	}
	void update(int x,int y,int val){
		x += n;
		T[x].update(y,val);
		segmetree ok;
		for(x >>= 1; x >= 1; x >>= 1){
			T[x].rupdate(y,T[x << 1].query(y,y + 1));
			T[x].update(y,T[x << 1 | 1].query(y,y + 1)); 
		}
	}
	ll query(int l,int b,int r,int t){
		l += n;
		r += n;
		r++,t++;
		ll ans = 0LL;
		while(l < r){
			if(l & 1)ans += T[l++].query(b,t);
			if(r & 1)ans += T[--r].query(b,t);
			l >>= 1, r >>= 1;
		}
		return ans;
	}
};
