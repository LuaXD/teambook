#include <bits/stdc++.h>
using namespace std;

/* no sirve en todos los jueces probar primero
int in() {
    int num, c;
    while((c = getchar_unlocked()) < '-');
    num = c - '0';
    while((c = getchar_unlocked()) >= '0') {
        num = (num<<3) + (num<<1) + (c-'0');
    }
    return num;
}
*/
int in(){int r=0,c;for(c=getchar();c<=32;c=getchar());if(c=='-') return -in();for(;c>32;r=(r<<1)+(r<<3)+c-'0',c=getchar());return r;}

#define DBG(x) cout << #x << ": " << x << "\n";
#define eb emplace_back
#define pb push_back
#define mp make_pair
#define mt make_tuple
