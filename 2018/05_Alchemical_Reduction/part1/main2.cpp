#include <iostream>
#include <string>
#include <stack>

inline bool unitsReact(char a, char b){
	return (a > b) ? a - b == 32 : b - a == 32;
}

int main(int argc, char* argv[]){
	std::string polymer;
	std::cin >> polymer;
	std::stack<char> stack;
	
	for(unsigned i = 0; i < polymer.size(); ++i){
		char c = polymer.c_str()[i];
		if(stack.empty()){
			stack.push(c);
		}else{
			if(unitsReact(stack.top(), c)){
				stack.pop();
			}else{
				stack.push(c);
			}
		}
	}
	
	std::cout << stack.size() << std::endl;
	
	return 0;
}