
ll T[1025][1025];
int n;

ll query(int x, int y)
{
	ll res = 0;
	for(int i = x; i >= 0; i = (i & (i+1)) - 1)
        for(int j = y; j >= 0; j = (j & (j+1)) - 1)
            res += T[i][j];
    return res;
}

void update(int x, int y, int val)
{
 	for(int i = x; i < n; i = (i | (i+1)))
        for(int j = y; j < n; j = (j | (j+1)))
            T[i][j] += val;
}
