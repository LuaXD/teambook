//Entrada: Una cadena cad(std::string), un long th
//Salida : La th-esima permutacion lexicografica de cad
string ipermutacion(string cad, long long int th){
	sort(cad.begin(), cad.end());
	string sol = "";
	int pos;
	for(int c = cad.size() - 1; c >= 0; c--){
		pos = th / fact[c];
		th %= fact[c];
		sol += cad[pos];
		cad.erase(cad.begin() + pos);
	}
	return sol;
}