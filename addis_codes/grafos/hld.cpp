// g++ -std=c++11 "hld.cpp" -o hld

/***
=============== <HLD> ===================
Complexity: O(N*log²(N))
Given a tree and asociative operation in the paths of this tree ask for many querys, and updates
in nodes or edges
Input of this example: 
N number of nodes, then N elements values in each node
then n - 1 conections
Q querys if T == 1 query on the path u,v
else update node U with value val.

Example problems: Spoj QTREE1 to QTREE6, toby and tree UVA
*/

#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5;
const int NEUTRO = 0; // a null value for my ST
int vec[maxn];
vector<int>G[maxn]; //the graph
//int idx[maxn]; // case with value in the edge
int op(int u,int v){// an operation for my path (using ST)
	//return __gcd(u,v);
	//return max(u,v);
	return u + v;
}
int n;
//ask to Branimir for information about this
struct SegmentTree{
	int T[2*maxn];
	void init(){
		memset(T,0,sizeof T);
	}
	void set(int pos,int val){
		pos += n;
		T[pos] = val;
		for(pos >>= 1; pos > 0; pos >>=1){
			T[pos] = op( T[pos << 1] , T[(pos << 1)|1] );
		}
	}
	int query(int l,int r){
		l += n;
		r += n;
		int ans = NEUTRO;
		while( l < r){
			if ( l & 1 ) ans = op(ans, T[l++] );
			if (r & 1 ) ans = op( ans, T[--r] );
			l >>= 1;
			r >>= 1;
		}
		return ans;
	}
};
struct hld{
	int ncad; // store actual number of chain
	int root; // the root of a tree generally 0 or 1
	int pos; // pos of node in chain
	
	int sz[maxn]; // store the subsize of subtrees
	int depth[maxn]; //depth of the node, useful for LCA via HLD
	int parent[maxn]; // useful for LCA 
	int where[maxn]; // where chain is the node? 
	//int edgepos[maxn]; // if the value is on the edge: stored in a node
	int chainIdx[maxn]; // position in the chain of the node
	int head[maxn]; // the head of the i-th chain
	//int val[maxn]; // if the value is on the edge
	SegmentTree tree; // this ST allow operations in the path
	
	void init(){//settings value, and process de HLD
		root = 0;
		ncad = 0;
		pos = 0;
		for(int i = 0; i <=n; i++){
			where[i] = head[i] = -1;
		}
		depth[root] = 0;
		dfs(root , -1);
		descompose(root);
		tree.init();
		/* case with values in edges
		for(int i=0;i<n;i++){
			tree.set(i,val[i]);
		}
		*/
	}
	
	
	///init descomposition
	void dfs(int u,int pu){
		sz[u] = 1; //init the sz of this subtree
		parent[u] = pu; // assign the parent
		for(int i = 0; i < G[u].size(); i++){
			int v = G[u][i];
			if ( v == pu )continue;
			//edgepos[idx[u][i]] = v;
			depth[v] = depth[u] + 1;
			dfs(v,u);
			sz[u] += sz[v];
		}
	}
	//descompose graph in HLD descomposition
	void descompose(int u){
		if( head[ncad] == -1)head[ncad] = u; // the head of ncad is u
		where[u] = ncad; // assign where tu node
		//val[pos] = cost; cost another parameter in descompose for graphs with values in edges
		chainIdx[u] = pos++; //assing pos to this node
		int maxi = -1, sc = -1; //finding a special child
		for(int v:G[u]){
			if( sz[v] > maxi && where[v] == -1){
				maxi = sz[v];
				sc = v;
			}
		}
		if(sc != -1)descompose(sc);
		//light nodes here:
		for(int v:G[u]){
			if(where[v] == -1){
				ncad++;
				descompose(v);
			}
		}
	}
	///end descomposition
	
	int lca(int u,int v){
		while(where[u]!=where[v]){
			if(depth[ head[ where[u] ] ] > depth[ head[ where[v] ] ])u = parent[ head[ where[u] ] ];
			else v = parent[ head[ where[v] ] ]; 
		}
		return depth[u] < depth[v] ? u:v;
	}
	
	void update(int u, int val){
		tree.set(chainIdx[u],val);
	}
	
	int query(int u,int v){
		// if ( u == v) return NEUTRO; value in edges
		int vChain = where[v];
		int ans = NEUTRO;
		while(true){
			int uChain = where[u];
			if(uChain == vChain){
				// return op(ans, tree.query( chainIdx[v] + 1, chainIdx[u] + 1) ); value in edges
				return op(ans, tree.query( chainIdx[v], chainIdx[u] + 1) );
			}
			int hu = head[uChain];
			ans = op( ans, tree.query(chainIdx[hu], chainIdx[u] + 1) );
			u = parent[hu];
		}
	}
	
	int Q(int u,int v){
		int L = lca(u,v);
		return op( query(u,L) , query(v,L) );
	}
}HLD;
int main(){
	//ios::sync_with_stdio(false);cin.tie(0);
	while(cin >> n){
		for(int i = 0; i < n; i++)G[i].clear();
		for(int i = 0; i < n; i++){
			cin >> vec[i];
		}
		for(int i = 1, u,v ; i < n; i++){
			cin >> u >> v;
			G[u].push_back(v);
			G[v].push_back(u);
			/* case with value in edges
			 G[u].push_back(make_pair(v,w));
			idx[u].push_back(i-1);
			G[v].push_back(make_pair(u,w));
			idx[v].push_back(i-1);
			 
			 */
		}
		HLD.init();
		for(int i = 0; i < n; i++){
			HLD.update(i, vec[i]);
		}
		int question;
		cin >> question;
		for(int i = 0, t, u ,v; i < question; i++){
			cin >> t >> u >> v;
			if( t == 1){
				cout << HLD.Q(u,v) << "\n";
			}
			else HLD.update(u,v);
		}
	}
}

