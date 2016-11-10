/***
=============== <Diameter and center of a tree> ===================
//Problem: Given a tree get the center (or centers)
/* the nodes in the tree that minimize the length of the longest path from it to any other node.
* *Finding tree centers:
 * If diameter length is even, then we have one tree center. If odd, then we have 2 centers.
 * E.g. 1-2-3-4-5   -> center is 3
 * E.g. 1-2-3-4-5-6 -> center is 3, 4
 * On other side, we can get the worst nodes through the center nodes.
 * A worst node is one that is an end of a diameter, so it has the worst tree height
Input:
* No
Output:
* No
dfs: calculate the diameter of the tree
* maxi stores the diameter
findingCenters() return the centers
Nodes in graph 1 to N careful with this
Complexity: O(N)
*/


vector<int>G[5010];
int maxi=-1,far;
int n;
int pre[5010];
int Queue[5010];

void dfs(int path,int u,int parent){
	pre[u]=parent;
	if(path>=maxi){
		maxi=path;
		far=u;
	}
	for(int v:G[u]){
		if(parent!=v){
			dfs(path+1,v,u);//path + w if the graph as weighted
		}
	}
}
pair<int,int> findingCenters(){
	maxi=-1;
	dfs(0,1,-1);
	dfs(0,far,-1);
	int t=far,L=0;
	while(t!=-1){
		Queue[L]=t;
		t=pre[t];
		++L;
	}
	int a=-1,b=-1;
	if(L&1){
		a=Queue[L/2];
	}
	else{
		a=min(Queue[L/2-1],Queue[L/2]),b=max(Queue[L/2-1],Queue[L/2]);
	}
	return {a,b};
}
