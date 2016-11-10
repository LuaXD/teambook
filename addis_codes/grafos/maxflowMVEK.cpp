// g++  "maxflowMVEK.cpp" -o run
/***
=============== <Max Flow with matriz Edmonds karp c++ version> ===================
//Given a graph with capacitys find the max-flow 

Nodes indexed 1 to N
* Complexity O(N²*E)
Problem for practice: UVA 820
*/
#define N 500
int cap[N][N], pre[N], n;
int s;//source
int t;//destination
bool bfs() {
    queue<int>q;
    q.push(s);
    memset(pre,-1,sizeof pre);
    pre[s]=s;
    while(!q.empty()){
        int u=q.front();q.pop();
        if(u==t)return true;
        for(int i=1;i<=n;i++){//nodes 1 to n
            if(pre[i]==-1&&cap[u][i])pre[i]=u,q.push(i);
        }
    }
    return false;
}

int maxFlow() {
    int mf=0,f,v;//max flow, flow for a path, the vertex
    while(bfs()){//while encountered a path  source to destination
        v=t;//min
        f=INT_MAX;//make this big enough
        while(pre[v]!=v){f=min(f,cap[pre[v]][v]),v=pre[v];}//finding the min capacity
        v=t;mf+=f;
        while(pre[v]!=v){cap[pre[v]][v]-=f,cap[v][pre[v]]+=f,v=pre[v];}//update the flow
    }
    return mf;
}
void init(){
	memset(cap,0,sizeof cap);
	//cap[u][v]+=capacidad,cap[v][u]+=capacidad
}
