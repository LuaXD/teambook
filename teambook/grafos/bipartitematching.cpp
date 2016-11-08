// g++ -std=c "bipartitematching.cpp" -o run
/***
=============== <MCBM max cardinality bipartite matching c++ version> ===================
Return the bipartite matching of a Graph
* Format of nodes: 1 to N
*/

const int N = 100010;
vector<int>G[N];
bool v[N];//for the greedy speed up
int match[N];
bool vis[N];
int n,m;
//calling aumenting path
bool aug(int u){
    if(vis[u])return false;
    vis[u]=true;
    for(int i=0;i<(int)G[u].size();++i){
		int r=G[u][i];
        if(match[r]==-1||aug(match[r])){
            match[r]=u;match[u]=r;return true;
        }
    }
    return 0;
}
int mc;
//findging all augmenting path's
int solve(){
	 bool check=true;
	 while(check){
        check=false;
        memset(vis,0,sizeof vis);
        for(int i=1;i<=n;++i){
			if(!v[i]&&match[i]==-1){
				bool op=aug(i);
				check|=op;
				mc+=op;
			}
		}
    }
    return mc;
}
void init(){
	memset(v,0,sizeof v);
	memset(vis,false,sizeof vis);
	mc=0;
	memset(match,-1,sizeof match);
    for(int i=0;i<=n;i++)G[i].clear();
}
void greedySpeedUp(){
	//greedy optimization, match with the first not matched
	for(int i=1;i<=n;++i){
         for(int j=0;j<(int)G[i].size();++j){
             if(match[G[i][j]]==-1){
				 match[G[i][j]]=i,match[i]=G[i][j],mc++,v[i]=true;break;
			}
        }
     }
}
