#include <iostream>
#include <vector>
#include <set>

int main(int argc, char* argv[]){
	std::vector<int> input;
	input.reserve(2000);//roughly expected input size
	{
		char sign = '+';
		int num = 0;
		while(std::cin >> sign >> num){
			input.push_back(sign == '+' ? num : -num);
		}
	}
	
	std::set<int> visited;
	int total = 0;
	while(true){
		for(int i = 0; i < input.size(); ++i){
			if(!visited.insert(total).second){
				std::cout << total << std::endl;
				return 0;
			}
			total += input[i];
		}
	}
	
	return 0;
}