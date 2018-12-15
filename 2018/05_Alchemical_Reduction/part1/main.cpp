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
	unsigned cur_idx = 1;
	for(unsigned i = 0; i < sz; ++i){
		if(unitsReact(buf[cur_idx - 1], polymer.c_str()[i])){
			cur_idx--;
		}else{
			buf[cur_idx] = polymer.c_str()[i];
			cur_idx++;
		}
	}
	buf[cur_idx] = '\0';
	std::cout << std::strlen(buf+1) << std::endl;
	delete[] buf;
	return 0;
}