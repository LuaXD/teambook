// g++ -std=c++11 "mo.cpp" -o run
/***
=============== <Mo> ===================
Contain a sample about Mo algorithm
Brief explanation when use Mo:
Explain where and when we can use above algorithm

As mentioned, this algorithm is offline, that means we cannot use it when we are forced to stick to given order of queries. 
 That also means we cannot use this when there are update operations. Not just that, there is one important possible limitation: 
We should be able to write the functions add and remove. There will be many cases where add is trivial but remove is not. 
One such example is where we want maximum in a range. As we add elements, we can keep track of maximum. But when we remove elements 
it is not trivial. Anyways in that case we can use a set to add elements, remove elements and report minimum. 
In that case the add and delete operations are O(log N) (Resulting in O(N * Sqrt(N) * log N) algorithm).

Suggestion first use the add operation, then the erase operation
Problem for practice: DQUERY spoj
Input: N, then N elements of array M querys with a range L,R
*/
const int MAXV = 1e6 + 10;
const int N = 30010;
const int M = 200010;
int cnt[MAXV];
int v[N];

struct query{
	int l,r,pos;
	query(){}
};
int n;
query qu[M];
int ans[M];

int ret = 0;
void add(int pos){
	pos = v[pos];
	cnt[pos]++;
	if(cnt[pos] == 1){
		ret++;
	}
}
void erase(int pos){
	pos = v[pos];
	cnt[pos]--;
	if(!cnt[pos])ret--;
}
int main(){
	n = in();
	for(int i = 0; i < n;i++){
		v[i] = in();
	}
	int block = ceil(sqrt(n));
	int q = in();
	for(int i = 0; i < q;i++){
		qu[i].l = in() - 1,qu[i].r = in() - 1,qu[i].pos = i;
	}
	sort(qu,qu + q,[&](const query &a,const query &b){
		if(a.l / block != b.l / block)
			return a.l / block < b.l / block;
		return a.r < b.r;
	});
	int l = 0, r = 0;
	for(int i = 0; i < q;i++){
		int nl = qu[i].l,nr = qu[i].r;
		while(l > nl){
			add(--l);
		}
		while(r <= nr){
			add(r++);
		}
		while(l < nl){
			erase(l++);
		}
		while(r > nr + 1){
			erase(--r);
		}
		
		ans[qu[i].pos] = ret;
	}
	for(int i = 0; i < q;i++)printf("%d\n",ans[i]);
}
