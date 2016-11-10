// g++ -std=c++11 "karatsuba.cpp" -o hld

/***
=============== <karatsuba> ===================
Complexity: O(N^1.7)
Call to karatsuba function paramter two vectors
* INPUT: two vectors A,B cointains the coeficients of the polynomail
* OUTPUT a vector coitains the coeficients of A * B
*/

int p,k;
vector<int> b,r;

void trim(vector<int>& a){
    while (a.size() > 0 && a.back() == 0) a.pop_back();
}

vector<int> multiply(const vector<int>& a, const vector<int>& b){
    vector<int> c(a.size() + b.size() + 1, 0);
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            c[i+j] += a[i] * b[j];
        }
    }
    trim(c);
    return c;
}
// a = a + b*(10^k)
void addTo(vector<int>& a, const vector<int>& b, int k){
    if (a.size() < b.size() + k) a.resize(b.size() + k);
    for (int i = 0; i < b.size(); i++) a[i+k] += b[i];
}
void subFrom(vector<int>& a, const vector<int>& b){
    for (int i = 0; i < b.size(); i++) a[i] -= b[i];
}
// a = a + b
void addTo(vector<int>& a, const vector<int>& b){
    addTo(a, b, 0);
}
vector<int> karatsuba(const vector<int>& a, const vector<int>& b)
{
    int alen = a.size();
    int blen = b.size();
    if (alen == 0 || blen == 0) return vector<int>();
    if (alen < blen) return karatsuba(b, a);
    if (alen < 50) return multiply(a, b);

    int half = alen / 2;
    vector<int> a0(a.begin(), a.begin() + half);
    vector<int> a1(a.begin() + half, a.end());
    vector<int> b0(b.begin(), b.begin() + min<int>(blen, half));
    vector<int> b1(b.begin() + min<int>(blen, half), b.end());

    vector<int> z0 = karatsuba(a0, b0);
    vector<int> z2 = karatsuba(a1, b1);
    addTo(a0, a1);
    addTo(b0, b1);
    vector<int> z1 = karatsuba(a0, b0);
    subFrom(z1, z0);
    subFrom(z1, z2);

    vector<int> res;
    addTo(res, z0);
    addTo(res, z1, half);
    addTo(res, z2, half + half);
    
    trim(res);
    return res;
}
