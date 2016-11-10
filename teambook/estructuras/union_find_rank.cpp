/*=============== <Union find rangos> ===================
Complexity: O(N)
index 0 to n - 1 warning
Complexity O(N)
*/
#define MAX 10005
int padre[ MAX ];   //Este arreglo contiene el padre del i-esimo nodo
int rango[ MAX ];   //profundidad de cada vertice
//Metodo de inicializacion
void MakeSet( int n ){
    for( int i = 0 ; i < n ; ++i ){
        padre[ i ] = i;      //Inicialmente el padre de cada vertice es el mismo vertice
        rango[ i ] = 0;      //Altura o rango de cada vertice es 0
    }
}
//Metodo para encontrar la raiz del vertice actual X
int Find( int x ){
    if( x == padre[ x ] ){          //Si estoy en la raiz
        return x;                   //Retorno la raiz
    }
    //else return Find( padre[ x ] ); //De otro modo busco el padre del vertice actual, hasta llegar a la raiz.
    else return padre[ x ] = Find( padre[ x ] ); //Compresion de caminos
}
//Metodo para unir 2 componentes conexas usando sus alturas (rangos)
void UnionbyRank( int x , int y ){
    int xRoot = Find( x );    //Obtengo la raiz de la componente del vertice X
    int yRoot = Find( y );    //Obtengo la raiz de la componente del vertice Y
    if( rango[ xRoot ] > rango[ yRoot ] ){ //en este caso la altura de la componente del vertice X es
                                           //mayor que la altura de la componente del vertice Y.
        padre[ yRoot ] = xRoot;            //el padre de ambas componentes sera el de mayor altura
    }
    else{                    //en este caso la altura de la componente del vertice Y es mayor o igual que la de X
        padre[ xRoot ] = yRoot;            //el padre de ambas componentes sera el de mayor altura
        if( rango[ xRoot ] == rango[ yRoot ] ){ //si poseen la misma altura
            rango[ yRoot ]++;              //incremento el rango de la nueva raiz
        }
    }
}