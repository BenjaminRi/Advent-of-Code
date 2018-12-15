#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[]){
	std::vector<std::string> strings;
	strings.reserve(2000);//roughly expected input size
	{
		std::string current;
		while(std::cin >> current){
			strings.push_back(current);
		}
	}
	
	for(int i = 0; i < strings.size(); ++i){
		for(int j = i+1; j < strings.size(); ++j){
			int chardiff = 0;
			{
				const char* c1 = strings[i].c_str();
				const char* c2 = strings[j].c_str();
				do{
					if(*c1 != *c2) chardiff++;
				}while(*(++c1) & *(++c2));
				if(*c1 || *c2) continue;//strings differ in length
			}
			
			if(chardiff == 1){
				const char* c1 = strings[i].c_str();
				const char* c2 = strings[j].c_str();
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