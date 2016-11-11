//infix to postfix with shunting yard, Halim interpretation
//plus eval function given a postfix return the result of the operation
//format: string like  ( x o x  ( x o x ) ) o=operation x=value
string s;
bool isOperator(string u){
	return u=="+"||u=="-"||u=="*"||u=="/";
}
bool precede(string u){
	if(u=="*"||u=="/")return true;
	return false;
}
void solve(){
	getline(cin,s);
	stack<string>st;
	vector<string>v;
	stringstream ss;
	ss<<s;
	while(ss>>s){
		if(isOperator(s)){
			while(!st.empty()&&isOperator(st.top())&&precede(st.top())>=precede(s)){
				v.push_back(st.top());st.pop();
			}
			st.push(s);
		}
		else{
			 if(s=="("){
				 st.push(s);
			}
			else{ 
				if(s==")"){
					while(!st.empty()&&st.top()!="("){
						v.push_back(st.top());st.pop();
					}
					if(!st.empty()&&st.top()=="(")st.pop();
				}
				else {
					v.push_back(s);
				}
			}
		}
	}
	while(!st.empty()){
		v.push_back(st.top());st.pop();
	}
	stack<double>stans;
	double x;		
	for(string eva:v){
		if(!isOperator(eva)){
			stringstream nu;
			nu<<eva;
			nu>>x;
			stans.push(x);
		}
		else{
			double a=stans.top();stans.pop();
			double b=stans.top();stans.pop();
			if(eva=="*")b*=a;
			if(eva=="/")b/=a;
			if(eva=="+")b+=a;
			if(eva=="-")b-=a;
			stans.push(b);
		}
	}
	cout<<fixed<<stans.top()<<"\n";
}
