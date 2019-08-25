#ifndef VECTORINOUT
#define VECTORINOUT

#include <iostream>
#include <vector>

//vector >> and << operators
std::ostream& operator<< (std::ostream& os, std::vector<int>& v){
	if (v.size()==0) return os;
	os << "[";
	std::vector<int>::iterator it = v.begin();
	for (std::vector<int>::iterator& i = it; i < v.end()-1; ++i) 
		os << *it << ", ";
	os << *it  << "]";
	return os;
}

std::istream& operator>> (std::istream& is, std::vector<int>& v){
	int ti;
	char tc;
	while (is >> tc && tc!= ']'){
		is >> ti;
		v.push_back(ti);
	}
	return is; 
}

#endif