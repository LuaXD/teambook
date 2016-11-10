// g++ -std=c++11 "articulationpointsandbridges.cpp" -o run
/***
=============== <Articulation points and bridges c++ version> ===================
Given a graph return a vector of paris with the bridges and a bool array art[] 
true if the node is an articulation point
* false otherwise
Graph nodes: 0 to N - 1
*/
using namespace std;
vector<int>G[10010];
int low[10010],num[10010],parent[10010],cc;
//cc is my timer
int art[10010];//bool for detect art point, int for detect how many nodes are connected to my articulation point
int root,rC;
int n;
vector<pair<int,int> >bridges;
void dfs(int u){
	low[u]=num[u]=cc++;
	for(int v:G[u]){
		if(num[v]==-1){
			parent[v]=u;
			if(u==root)rC++;
			dfs(v);
			if(low[v]>=num[u])art[u]++;//is a articulation point
			if(low[v]>num[u])bridges.push_back({u,v});//this is a bridge
			low[u]=min(low[u],low[v]);
		}
		else if(v!=parent[u]){
				low[u]=min(low[u],num[v]);
		}
	}
}
void init(){
	bridges.clear();
	for(int i=0;i<n;i++){
		art[i]=low[i]=0;
		num[i]=parent[i]=-1;
		G[i].clear();
	}
	cc=0;
}
void callARTBRID(){
	for(int i=0;i<n;i++){
		if(num[i]==-1){
			root=i,rC=0;dfs(i);
			art[root]=(rC>1);
		}
	}
}
