#include<sstream>
#include "stringlib.h"
vector<string> split(const string& s,char delim){
	stringstream ss(s);
	string item;
	vector<string> elems;
	
	while(getline(ss,item,delim)){
		elems.push_back(item);
	}
	return elems;
}
