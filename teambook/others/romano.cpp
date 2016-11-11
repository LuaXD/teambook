#include <bits/stdc++.h>
using namespace std;
map<int,string>cvt;

string aromano(int n){
	cvt[1000] = "M";cvt[900] = "CM",cvt[500] = "D", cvt[400] = "CD";
	cvt[100] = "C";cvt[90] = "XC"; cvt[50] = "L";
	cvt[40] = "XL";cvt[10] = "X";cvt[9] = "IX";cvt[5] = "V"; cvt[4] = "IV";
	cvt[1] = "I";
	string ans = "";
	for(map<int,string>::reverse_iterator it = cvt.rbegin();it != cvt.rend();it++)
		while(n >= it->first){
			ans += it->second;
			n -= it->first;
		}
	return ans;
}
map<string,int>crn;
int anumero(string R){
	map<char, int> crn;
	crn['I'] = 1;   crn['V'] = 5;   crn['X'] = 10;   crn['L'] = 50;
	crn['C'] = 100; crn['D'] = 500; crn['M'] = 1000;
	int value = 0;
	for (int i = 0; R[i]; i++)
		if (i + 1 < R.size() && crn[R[i]] < crn[R[i+1]]) {
			value += crn[R[i+1]] - crn[R[i]];
			i++; 
		}                                           
		else value += crn[R[i]];
	return value;
}
