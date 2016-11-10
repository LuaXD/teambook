// g++ -std=c++11 "maxflowNMEK.cpp" -o run
/***
=============== <Max Flow with-out matriz Edmonds karp c++ version> ===================
//Given a graph with capacitys find the max-flow 

Nodes indexed 1 to N
* Complexity O(N²*E)
Problem for practice: UVA 820
* Input N number of nodes,
* M edges conections
* compute the flow with source 1 and sink N
*/
using namespace std;
const int N = 110;
const int M = 10010 * 2;
vector<int>G[N];
int kend[M], cap[M], cost[M];
int edge = 0;
int s,t;
void add(int u,int v,int c){
	int forward = edge * 2, backward = edge * 2 + 1;
	kend[forward] = v;
	cap[forward] = c;
	G[u].push_back(forward);
	kend[backward] = u;
	cap[backward] = 0;
	G[v].push_back(backward);
	edge++;
}
int vis[M],pre[M],pret[M];
bool bfs(){
	for(int i = 0; i <= 100;i++)vis[i] = false;
	vis[s] = true;
	queue<int>q;
	q.push(s);
	while(!q.empty()){
		int u = q.front();q.pop();
		for(int edge:G[u]){
			int v = kend[edge];
			if(cap[edge] > 0 && !vis[v]){
				vis[v] = true;
				pre[v] = u;
				pret[v] = edge;//the edge store the information 
				q.push(v);
			}
		}
	}
	return vis[t];
}
int max_flow(){
	int totf = 0LL;
	while(bfs()){
		int minflow = INT_MAX;
		for(int x = t; x != s; x = pre[x]){
			minflow = min(minflow,cap[pret[x]]);
		}
		for(int x = t; x != s; x = pre[x]){
			cap[pret[x]] -= minflow;
			cap[pret[x] ^ 1] += minflow;
		}
		totf += minflow;
	}
	return totf;
}
int main(){
	int n,m;
	scanf("%d %d",&n,&m);
	for(int i = 0,u,v,ca; i < m;i++){
		scanf("%d %d %d",&u,&v,&ca);
		add(u,v,ca);
	}
	s = 1, t = n;
	printf("%lld\n",max_flow());
}

