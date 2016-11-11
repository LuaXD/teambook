#include <cstdio>
#include <vector>
#include <iostream>
#include <cstring>

using namespace std;

#define MAX_LEN 100000
#define ALPH_SIZE 123
typedef char tipo;
tipo s[MAX_LEN+1];
int N,sa[MAX_LEN],rk[MAX_LEN];
int cont[MAX_LEN],nxt[MAX_LEN];
bool bh[MAX_LEN+1],b2h[MAX_LEN+1];

void build_suffix_array(){
    N = strlen(s); //size for ints
    memset(cont,0,sizeof(cont));
    for(int i = 0;i<N;++i) ++cont[s[i]];
    for(int i = 1;i<ALPH_SIZE;++i) cont[i] += cont[i-1];
    for(int i = 0;i<N;++i)sa[--cont[s[i]]] = i;
    for(int i = 0;i<N;++i){
        bh[i] = (i==0 || s[sa[i]] != s[sa[i-1]]);
        b2h[i] = false;
    }
    for(int H = 1;H<N;H <<= 1){
        int buckets = 0;
        for(int i = 0,j;i<N;i = j){
            j = i+1;
            while(j<N && !bh[j]) ++j;
            nxt[i] = j;
            ++buckets;
        }
        if(buckets==N) break;
        for(int i = 0;i<N;i = nxt[i]){
            cont[i] = 0;
            for(int j = i;j<nxt[i];++j)
                rk[sa[j]] = i;
        }
        ++cont[rk[N-H]];
        b2h[rk[N-H]] = true;
        for(int i = 0;i<N;i = nxt[i]){
            for(int j = i;j<nxt[i];++j){
                int s = sa[j]-H;
                if(s>=0){
                    int head = rk[s];
                    rk[s] = head+cont[head];
                    ++cont[head];
                    b2h[rk[s]] = true;
                }
            }
            for(int j = i;j<nxt[i];++j){
                int s = sa[j]-H;	
                if(s>=0 && b2h[rk[s]]){
                    for(int k = rk[s]+1;!bh[k] && b2h[k];++k)
                        b2h[k] = false;
                }
            }
        }
        for(int i = 0;i<N;++i){
            sa[rk[i]] = i;
            bh[i] |= b2h[i];
        }
    }
}
vector<int> kasai(){
    int n = N,k = 0;
    vector<int> lcp(n,0);
    vector<int> rank(n,0);
    for(int i=0; i<n; i++) rank[sa[i]]=i;
    for(int i=0; i<n; i++, k?k--:0){
        if(rank[i]==n-1) {k=0; continue;}
        int j=sa[rank[i]+1];
        while(i+k<n && j+k<n && s[i+k]==s[j+k]) k++;
        lcp[rank[i]]=k;
    }
    return lcp;
}
