// g++ -std=c++11 "maxflowmincost.cpp" -o run
/***
=============== <Max flow-min cost c++ version> ===================
Given a grapth with edges with a capacity C and weight D
* compute the max-flow min cost
Edmond karps idea
* Complexity O(v²*E*log(v))
Problem for practice: Dijkstra Dijkstra uva
*/
#define REP(i,j,k) for(int (i)=(j);(i)<(k);++(i))
#define MP make_pair

using namespace std;

#define MAXN 500
#define MAXM MAXN * 5
typedef vector<int> VI;
typedef long long ll;
const int INF = 1E9; // $infinity$: be careful to make this big enough!!!
int S; // source
int T; // sink
int FN; // number of nodes
int FM; // number of edges (initialize this to 0)
// ra[a]: edges connected to a (NO MATTER WHICH WAY!!!); clear this in the beginning
VI ra[MAXN];
int kend[MAXM], cap[MAXM], cost[MAXM]; // size: TWICE the number of edges

// Adds an edge from a to b with capacity c and cost d and returns the number of the new edge

int addedge(int a, int b, int c, int d) {
	int i = 2*FM;
	kend[i] = b;
	cap[i] = c;
	cost[i] = d;
	ra[a].push_back(i);
	kend[i+1] = a;
	cap[i+1] = 0;
	cost[i+1] = -d;
	ra[b].push_back(i+1);
	FM++;
	return i;
}
int n;
int dst[MAXM], pre[MAXM], pret[MAXM];
//finding the shortest path via fanding duan, also it works with bellman ford
//or dijkstra (careful of negative cycles)
bool spfa(){
	REP(i,0,FN) dst[i] = INF;
	dst[S] = 0;
	queue<int> que; que.push(S);
	while(!que.empty()){
		int x = que.front(); que.pop();
		for (int t : ra[x]){
			int y = kend[t], nw = dst[x] + cost[t];
			if(cap[t] > 0 && nw<dst[y]){
				dst[y] = nw; pre[y] = x; pret[y] = t; que.push(y);
			}
		}
	}
	return dst[T]!=INF;
}
// returns the maximum flow and the minimum cost for this flow
pair<ll,ll> solve(){
	ll totw = 0, totf = 0;
	while(spfa()){
		int minflow = INF;
		for (int x = T; x!=S; x = pre[x]){
			minflow = min(minflow, cap[pret[x]]);
		}
		for (int x = T; x!=S; x = pre[x]){
			cap[pret[x]] -= minflow;
			cap[pret[x]^1] += minflow;
		}
		totf += minflow;
		totw += minflow*dst[T];
	}
	return make_pair(totf, totw);
}
void init(){
	FN=4*n+15;//make this big n=number of nodes of the graph
	FM=0;
	S=0,T=n+1;
	for(int i=0;i<FN;i++)ra[i].clear();//clear the graph be careful
}
