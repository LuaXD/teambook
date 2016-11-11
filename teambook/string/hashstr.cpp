typedef unsigned long long ull;
const int p = 500009;
int x;
long long pw[500010];
long long h[500010];
long long poly(const string &t,int le,int ri){
	long long h = 0LL;
	string s = "";
	for(int i = le; i < ri;i++)s += t[i];
	for(int i = s.size() - 1; i >= 0; i--){
		h = ( ( h % p ) * ( x % p ) + s[i] ) % p;
	}
	return h;
}
bool equal(const string &s,const string &t,int ini){
	for(int i = 0; i < t.size();i++){
		if(s[i + ini] != t[i])return false;
	}
	return true;
}
int main() {
    x = (rand() % (p - 1) ) + 1;
	pw[0] = 1;
    for(int i = 1; i <= 5e5 + 5;i++){
		pw[i] = (pw[i - 1] * x % p) % p;
	}
	string pattern, text;
	cin >> pattern >> text;	
	long long y = 1LL;
	h[text.size() - pattern.size()] = poly(text, text.size() - pattern.size(), text.size()); 	
	for(int i = 0; i < pattern.size(); i++){
		y = ( y % p * x % p ) % p;
	}
	for(int i = text.size() - pattern.size()  - 1; i>= 0; i--){
		long long cal = (text[i] - (y * text[i + pattern.size()]) % p + p ) % p;
		if(cal < 0) cal += p;
		h[i] = ( ( x * h[i + 1] ) % p + cal) % p;
	}
	vector<int>res;
	int pHash = poly(pattern,0,pattern.size());
	for(int i = 0; i <= text.size() - pattern.size(); i++){
		if(pHash != h[i])continue;
		if(equal(text,pattern,i))res.push_back(i);
	}
	for(auto u:res)cout << u << " ";
	cout << "\n";
    return 0;
}
