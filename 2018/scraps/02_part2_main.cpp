#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

bool reverse_comp(std::string a, std::string b){
	std::string::reverse_iterator a_it;
	std::string::reverse_iterator b_it;
	for(
		a_it = a.rbegin(),
		b_it = b.rbegin();
		a_it != a.rend() &&
		b_it != b.rend();
		a_it++,
		b_it++){
		if(*a_it != *b_it) return *a_it < *b_it;
	}
	if(a_it == a.rend() && b_it == b.rend()) return false;
	if(a_it == a.rend()) return true;
	return false; //b_it == b.rend()
}

int main(int argc, char* argv[]){
	std::vector<std::string> strings;
	strings.reserve(2000);//roughly expected input size
	{
		std::string current;
		while(std::cin >> current){
			strings.push_back(current);
		}
	}
	
	for(unsigned pass = 0; pass < 2; ++pass){
		if(pass == 0) std::sort(strings.begin(), strings.end());
		if(pass == 1) std::sort(strings.begin(), strings.end(), reverse_comp);
		
		for(int i = 0; i < strings.size()-1; ++i){
			int chardiff = 0;
			{
				const char* c1 = strings[i].c_str();
				const char* c2 = strings[i+1].c_str();
				do{
					if(*c1 != *c2) chardiff++;
				}while(*(++c1) & *(++c2));
				if(*c1 || *c2) continue;//strings differ in length
			}
			
			if(chardiff == 1){
				const char* c1 = strings[i].c_str();
				const char* c2 = strings[i+1].c_str();
				do{
					if(*c1 == *c2) std::cout << *c1;
				}while(*(++c1) & *(++c2));
				std::cout << std::endl;
				return 0;
			}
		}
	}
	
	return 0;
}