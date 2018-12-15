#include <iostream>
#include <string>
#include <cstring>

//This problem could be solved with a stack but
//a highly optimized C-style solution is more fun

inline bool unitsReact(char a, char b){
	return (a > b) ? a - b == 32 : b - a == 32;
}

int main(int argc, char* argv[]){
	std::string polymer;
	std::cin >> polymer;
	
	
	const unsigned sz = polymer.size();
	char* buf = new char[sz + 2];
	buf[0] = ' '; //dummy unit at base
	
	unsigned lowest = polymer.size()+1;
	for(char ignore = 'A'; ignore <= 'Z'; ++ignore){	
		//Potential for further optimization:
		//First reduce, then ignore letters and reduce more
		unsigned cur_idx = 1;
		for(unsigned i = 0; i < sz; ++i){
			char c = polymer.c_str()[i];
			if(c == ignore || c == ignore + 32) continue;
			if(unitsReact(buf[cur_idx - 1], c)){
				cur_idx--;
			}else{
				buf[cur_idx] = c;
				cur_idx++;
			}
		}
		buf[cur_idx] = '\0';
		unsigned current = std::strlen(buf+1);
		if(current < lowest){
			lowest = current;
		}
	}
	
	std::cout << lowest;
	
	delete[] buf;
	return 0;
}