vector<int> FindOccurrences(const string& pattern, const string& text) {
	vector<int> result;
	int minIndex = 0,maxIndex = text.size();
	while(minIndex < maxIndex){
		int mid = (minIndex + maxIndex) >> 1;
		if(cmp(pattern,sa[mid]) > 0)minIndex = mid + 1;
		else maxIndex = mid;
	}
	int start = minIndex;
	maxIndex = text.size();
	while(minIndex < maxIndex){
		int mid = (minIndex + maxIndex) >> 1;
		if(cmp(pattern,sa[mid]) < 0)maxIndex = mid;
		else minIndex = mid + 1;
	}
	int end = maxIndex;
	for(int i = start;  i < end;i++){
		result.push_back(sa[i]);
	}
	return result;
}
