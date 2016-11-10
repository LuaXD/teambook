// g++ -std=c++11 "twosat.cpp" -o run
/***
=============== <Two Sat> ===================
Complexity: O(N)
Input: number of variables, then number of clause clauses in format (u or v) 
if u,v > 0 then is equivalent to u,v
if u,v < 0 then is equivalent to ¬u, ¬v
Output: UNSATISFIABLE can't find a solution
SATISFIABLE if exist a solution then print the assignment of all variables (negative for xi = false)

Examples:
Input:
3 3
1 -3
-1 2
-2 -3
Output 
SATISFIABLE
1 2 -3
* 
Input
1 2
1 1
-1 -1
Output
UNSATISFIABLE
*/
#include <bits/stdc++.h>
using namespace std;
vector<int>G[2][2000010],G2[2000010];
int n, m;
int scc[2000010];
bool vis[2000010];
vector<int>comp[2000010];
int assign[2000010];
int cc = 0;
stack<int>st;
vector<int>sta;
void dfs(int u,int type){
	if(scc[u] != -1)return;
	scc[u] = cc;
	for(int v:G[type][u]){
		dfs(v,type);
	}
	if(!type)st.push(u);
}
void topo(int u){
	if(vis[u])return;
	vis[u] = true;
	for(int v:G2[u])topo(v);
	sta.push_back(u);
}
void buildGraphWitouthLoop(){
	for(int i = 0;i < 2 * n;i++){
		for(int j = 0;j < G[0][i].size();j++){
			if(scc[i] != scc[G[0][i][j]])
				G2[scc[i]].push_back(scc[G[0][i][j]]);
		}
	}
}
int main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin >> n >> m;
    for(int i = 0,u,v; i < m;i++){
		cin >> u >> v;
		int uu = (u > 0?(u - 1) * 2:(-u - 1) * 2 + 1);
		int vv = (v > 0?(v - 1) * 2:(-v - 1) * 2 + 1);
	//	cout << uu << " " << (uu ^ 1) << "\n";	
		G[0][uu ^ 1].push_back(vv);
		G[0][vv ^ 1].push_back(uu);
		G[1][vv].push_back(uu ^ 1);
		G[1][uu].push_back(vv ^ 1);
	}
	memset(scc,-1,sizeof scc);
	for(int i = 0; i < 2 * n;i++){
		if(scc[i] == -1)dfs(i,0);
	}
	memset(scc,-1,sizeof scc);
	while(!st.empty()){
		int u = st.top();st.pop();
		if(scc[u] == -1){
			dfs(u,1);
			cc++;
		}
	}
	bool unsat = false;
	for(int i = 0; i < 2 * n;i++){
		if(scc[i] == scc[i ^ 1])unsat = true;
		comp[scc[i]].push_back(i);
	}
	if(unsat){
		return cout << "UNSATISFIABLE",0;
	}
	cout << "SATISFIABLE\n";
	buildGraphWitouthLoop();
	for(int i = 0; i < 2 * n;i++){
		if(!vis[i])topo(i);
	}
	for(int u:sta){//inverse of topological sort
		for(int v:comp[u]){//transitivite Skew-Symmetry
			if(!assign[v]){
				assign[v] = 1;
				assign[v ^ 1] = -1;
			}
		}
	}
	for(int i = 0,j = 1; i < 2 * n; i += 2,j++){
		cout << (j) * (assign[i]) << " ";
	}
    return 0;
}

