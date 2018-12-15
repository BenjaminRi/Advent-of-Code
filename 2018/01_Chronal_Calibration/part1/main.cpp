#include <iostream>


int main(int argc, char* argv[]){
	int total = 0;
	{
		char sign = '+';
		int num = 0;
		while(std::cin >> sign >> num){
			total += sign == '+' ? num : -num;
		}
	}
	std::cout << total << std::endl;
	
	return 0;
}