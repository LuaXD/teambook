map<char,int>fo;//first ocurrence
map<char,vector<int> >count;//count the i-th ocurrence of symbol
string first;//first colum of bwt
string alpha = "ACGT$";//change this 
void preprocess(const string& bwt) {//recieves a BWT
	string ans = "";
	first = bwt;
	sort(first.begin(),first.end());
	for(int i = 0;first[i];i++){
		if(!fo.count(first[i]))fo[first[i]] = i;
	}
	for(char u:alpha)count[u].push_back(0);
	for(int i = 1; i <= bwt.size();i++){
		for(char u:alpha)
			count[u].push_back(count[u].back() + (bwt[i - 1] == u));
	}
}
//return the number of ocurrences of the pattern
int bwtmatch(int bot,string &pattern){
	int top = 0;
	while(top <= bot){
		if(pattern.size()){
			char letter = pattern.back();
			pattern.pop_back();
			if(count[letter][bot + 1]){
				top = fo[letter] + count[letter][top];
				bot = fo[letter] + count[letter][bot + 1] - 1;
			}
			else return 0;
		}
		else return bot - top + 1;
	}
	return 0;
}
