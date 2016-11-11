int negative_cycle(vector<vector<int> > &G, vector<vector<int> > &cost) {
  //write your code here
  bool nc = false;
  int n = G.size();
  vector<int>dist(n,INT_MAX / 2);
  dist[0] = 0;
  for(int i = 0; i < n - 1; i++)
	for(int u = 0; u < n;u++)
		for(int j = 0; j < G[u].size();j++){
			int v = G[u][j];
			int w = cost[u][j];
			dist[v] = min(dist[v], dist[u] + w);
		}
  for(int u = 0; u < n;u++){
	for(int j = 0; j < G[u].size();j++){
		int v = G[u][j];
		int w = cost[u][j];
		if(dist[v] > dist[u] + w)nc = true;
	}  
  }
  return nc;
}
