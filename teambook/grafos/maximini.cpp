// g++ -std=c++11 "maximini.cpp" -o run
/***
=============== <maximini c++ version> ===================
Given a weighted graph return the maximini (the maximun of the minimum)
or the minimax (the minimum of the maximum) in the path a,b
* 
Minimax as definded as: finding the minimum of maximum edge weight among all posible paths 
* between two verrtices a to b, the cost for a path fron a to b is determined by maximum edge
* weight along this path. Among all these possible paths from a to b, pick the one with the minimum
* ax-edge-weight
* Complexity O(E*log(E) + V + E)
* 
Problem for practice: UVA 534,544
*/
int n;
pair<int,pair<int,int> >Edges[20000];
int t;
map<string,int>mp;
int parent[210];
pair<int,int>child[210];
bool vis[210];
vector<pair<int,int> >G[210];

int find(int u){return u==parent[u]?u:parent[u]=find(parent[u]);}
void Union(int u,int v){
	int pu=find(u),pv=find(v);
	if(pu!=pv){
		parent[pv]=pu;
	}
}
int mst(int a,int b){
	sort(Edges,Edges+t);
	reverse(Edges,Edges+t);//don't reverse for the minimax
	for(int i=0;i<=200;i++)parent[i] = i;
	int w,u,v, maximini = 1e8, minimax = 0;
	for(int i=0;i<t;i++){
		tie(w,u,v) = make_tuple(Edges[i].first, Edges[i].second.first, Edges[i].second.second);
		if(find(u) != find(v)){
			Union(u,v);
			G[u].push_back({v,w});
			G[v].push_back({u,w});
		}
	}
	queue<int>q;
	q.push(a);
	vis[a]=true;
	while(!q.empty()){
		int u = q.front();q.pop();
		//if(u==1)break;
		for(pair<int,double>node: G[u]){
			if(!vis[node.first]){
				vis[node.first] = true;
				q.push(node.first);
				//maximini=max(maximini,node.second);
				child[node.first].first = u;
				child[node.first].second = node.second;
			}
		}
	}
	for(int t = b;t != -1;t = child[t].first){
		//cout<<t<<" "<<child[t].second<<"\n";
		//minimax=max(minimax,child[t].second);
		maximini = min(maximini,child[t].second);
	}
	return maximini;
}

