/*=============== <Union find rangos> ===================
Complexity: O(N)
index 0 to n - 1 warning
Complexity O(N)
*/
#define MAX INSERTE_VALOR_AQUI
int padre[MAX]; 
int rango[MAX];
void MakeSet(int n){
    for (int i = 0 ; i < n ; ++i) {
        padre[i] = i; rango[i] = 0; }
}
int Find(int x) {
    if(x == padre[x])
        return x;
    return padre[x] = Find(padre[x]);
}
void UnionbyRank(int x , int y){
    int xRoot = Find(x);
    int yRoot = Find(y);
    //el padre de ambas componentes sera el de mayor altura
    if(rango[xRoot] > rango[yRoot])//X tiene mas altura que Y
        padre[yRoot] = xRoot;
    }else{//Y >= X
        padre[xRoot] = yRoot;
        if(rango[xRoot] == rango[yRoot])//si poseen la misma altura
            rango[yRoot]++;//incremento el rango de la nueva raiz
    }
}
