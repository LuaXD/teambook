#include <iostream>  
#include <string.h>  
#include <algorithm>  
#include <stdio.h>  
#include <vector>

typedef long long int number;
using namespace std;
const int INSERTE_VALOR =  90050;
vector<int> alpha;

/*################### Suffix Automata ###################*/
const int N = INSERTE_VALOR;//maxima longitud de la cadena
struct State {  //OJO!!! tamanio del alfabeto, si MLE -> map
    State *pre,*go[26];//se puede usar un map<char, State*> go
    int step;  
    void clear() {  
        pre=0;  
        step=0;  
        memset(go,0,sizeof(go));//go.clear();
    }  
} *root,*last;    
State statePool[N * 2],*cur;    
void init() {  
    cur=statePool;  
    root=last=cur++;  
    root->clear();  
} 
void Insert(int w) {  
    State *p=last;  
    State *np=cur++;  
    np->clear();  
    np->step=p->step+1;  
    while(p&&!p->go[w])  
        p->go[w]=np,p=p->pre;  
    if(p==0)  
        np->pre=root;  
    else {  
        State *q=p->go[w];  
        if(p->step+1==q->step)  
            np->pre=q;  
        else {  
            State *nq=cur++;  
            nq->clear();  
            memcpy(nq->go,q->go,sizeof(q->go));//nq->go = q->go; para mapa
            nq->step=p->step+1;  
            nq->pre=q->pre;  
            q->pre=nq;  
            np->pre=nq;  
            while(p&&p->go[w]==q)  
                p->go[w]=nq, p=p->pre;  
        }  
    }  
    last=np;  
}
/*################### Suffix Automata ###################*/

/*################### Algunas aplicaciones ###################*/
//Obtiene el LCSubstring de 2 cadenas en O(|A| + |B|)
string lcs(char A[N], char B[N]) {
    int n,m;  
    n = strlen(A); m = strlen(B);
    //Construccion: O(|A|)
    //solo hacerlo una vez si A no cambia
    init();  
    for(int i=0; i<n; i++)  
        Insert(A[i]-'a'); //Fin construccion
    //LCS: O(|B|)
    int ans = 0, len = 0, bestpos = 0;  
    State *p = root;  
    for(int i = 0; i < m; i++) {  
        int x = B[i]-'a';  
        if(p->go[x]) {  
            len++;  
            p = p->go[x];  
        } else {  
            while (p && !p->go[x]) p = p->pre;  
            if(!p) p = root, len = 0;  
            else   len = p->step+1, p = p->go[x];  
        }
        if (len > ans)
            ans = len, bestpos = i;
    }
    //return ans; //solo el tamanio del lcs
    return string(B + bestpos - ans + 1, B + bestpos + 1);
}

/*Numero de subcadenas distintas + 1(subcadena vacia) en O(|A|)
OJO: Por alguna razon Suffix Array es mas rapido
Se reduce a contar el numero de paths que inician en q0 y terminan
en cualquier nodo. dp[u] = # de paths que inician en u
- Se debe construir el automata en el main(init y Insert's)
- Setear dp en -1
*/
number dp[N * 2];
number num_dist_substr(State *u = root) {
    if (dp[u - statePool] != -1) return dp[u - statePool];
    number ans = 1;//el path vacio que representa este nodo
    for (int v = 0; v < 26; v++)//usar for (auto) para mapa
        if (u->go[v])
            ans += num_dist_substr(u->go[v]);
    return (dp[u - statePool] = ans);
}

/*Suma la longitud de todos los substrings en O(|A|)
- Construir el automata(init y insert's)
- Necesita el metodo num_dist_substr (el de arriba)
- setear dp's en -1
*/
number dp1[N * 2];
number sum_length_dist_substr(State *u = root) {
    if (dp1[u - statePool] != -1) return dp1[u - statePool];
    number ans = 0;//el path vacio que representa este nodo
    for (int v = 0; v < 26; v++)//usar for (auto) para mapa
        if (u->go[v])
            ans += (num_dist_substr(u->go[v]) + sum_length_dist_substr(u->go[v]));
    return (dp1[u - statePool] = ans);   
}

/*
Pregunta si p es subcadena de la cadena con la cual esta construida
el automata.
Complejidad: - Construir O(|Texto|) - solo una vez (init e insert's)
             - Por Consulta O(|patron a buscar|)
*/
bool is_substring(char p[N]) {
    State *u = root;
    for (int i = 0; p[i]; i++) {
        if (!u->go.count(p[i]))//esta con map!!!
            return false;
        u = u->go[p[i]];//esta con map!!!
    }
    return true;
}
/*####################################################################*/
//EL RESTO ESTA SIN PROBAR
/*
number K;
string ans = "";
number path;
void kth_lex_substring(State *u = root) {
    for (int v = 0; v < 26; v++)
        if (u->go[v]) {
            path++;
            if (path == K) {
                ans.push_back('a' + v);
                return;
            }
            kth_lex_substring(u->go[v]);
            if (path == K) {
                ans.push_back('a' + v);
                return;
            }
        }
}*/
char A[N],B[N];
int main() {  
    /*
    //LCS de 2 cadenas
    //Ej: https://www.codechef.com/problems/SSTORY
    scanf("%s%s",A,B);  
    string ans = lcs(A, B);
    if (ans.size() > 0)
        printf("%s\n", ans.c_str());
    printf("%d\n", (int)ans.size());
    */
    
    /*
    //cantidad de subcadenas distintas
    //http://www.spoj.com/problems/DISUBSTR/
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%s", A);
        init();
        vector<bool> letters_used(257);
        int n = 0;
        for (int i = 0; A[i]; i++) {
            letters_used[A[i]] = true;
            Insert(A[i]);
            n++;
        }
        alpha.clear();
        for (int i = 0; i < 257; i++)
            if (letters_used[i])
                alpha.push_back(i);
        for (int i = 0, lim = 2 * n; i <= lim; i++)
            dp[i] = -1;
        printf("%d\n", num_dist_substr() - 1);
    }*/

    /*
    //suma de longitud de subcadenas distintas
    //http://s8pc-2.contest.atcoder.jp/tasks/s8pc_2_e
    scanf("%s", A);
    init();
    for (int i = 0; A[i]; i++)
        Insert(A[i] - 'a');
    memset(dp, -1, sizeof(dp));
    memset(dp1, -1, sizeof(dp1));
    printf("%lld\n", sum_length_dist_substr());
    //printf("%lld\n", num_dist_substr());*/

    /*
    //K-esimo substring lexicografico
    scanf("%s", A);
    init();
    for (int i = 0; A[i]; i++)
        Insert(A[i] - 'a');
    int q;
    scanf("%d", &q);
    while (q--) {
        scanf("%lld", &K);
        ans.clear();
        path = 0;
        kth_lex_substring();
        printf("%s\n", ans.c_str());
    }*/

    scanf("%s", A);
    init();
    for (int i = 0; A[i]; i++)
        Insert(A[i] - 'a');
    int q;
    scanf("%d", &q);
    while (q--) {
        scanf("%s", B);
        printf("%c\n", is_substring(B)?'Y':'N');
    }
    return 0;  
}  
