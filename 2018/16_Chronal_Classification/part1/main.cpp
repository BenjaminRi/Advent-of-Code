#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <exception>

class Regs{
	public:
		inline int& operator[](const unsigned idx){
			if(idx < sizeof(array)/sizeof(array[0])) return array[idx];
			throw std::invalid_argument("Invalid index");
		}
		inline bool operator==(const Regs& other){
			return !memcmp(array, other.array, sizeof(array));
		}
	private:
		int array[4];
};

struct Instr{
	int op;
	int in1;
	int in2;
	int out;
};

bool clear_input(){
	std::cin.clear();
	return false;
}

int main(int argc, char* argv[]){
	std::vector<Instr> program;
	program.reserve(2000);//roughly expected input size
	
	bool reading = true;
	Instr instr;
	Regs r_before;
	Regs r_after;
	std::string s;
	char pad;
	
	int geq3_possible_ops = 0;
	
	while(reading){
		if(std::cin >> instr.op >> instr.in1 >> instr.in2 >> instr.out || clear_input()){
			program.push_back(instr);
		}else if(
			std::cin >> s >> pad >> r_before[0] >> pad >> r_before[1] >> pad >> r_before[2] >> pad >> r_before[3] >> pad >> 
			instr.op >> instr.in1 >> instr.in2 >> instr.out >>
			s >> pad >> r_after[0] >> pad >> r_after[1] >> pad >> r_after[2] >> pad >> r_after[3] >> pad){
				
				const bool debug_out = false;
				if(debug_out){
					//std::cout << s << std::endl;
					std::cout << r_before[0] << "/" << r_before[1] << "/" << r_before[2] << "/" << r_before[3] << std::endl;
					std::cout << instr.op << "/" << instr.in1 << "/" << instr.in2 << "/" << instr.out << std::endl;
					std::cout << r_after[0] << "/" << r_after[1] << "/" << r_after[2] << "/" << r_after[3] << std::endl;				
					std::cout << std::endl;
				}
				int possible_ops = 0;
				
				Regs curr;
				//Addition
				//addr
				curr = r_before;
				curr[instr.out] = curr[instr.in1] + curr[instr.in2];
				possible_ops += r_after == curr;
				//addi
				curr = r_before;
				curr[instr.out] = curr[instr.in1] + instr.in2;
				possible_ops += r_after == curr;
				
				//Multiplication
				//mulr
				curr = r_before;
				curr[instr.out] = curr[instr.in1] * curr[instr.in2];
				possible_ops += r_after == curr;
				//muli
				curr = r_before;
				curr[instr.out] = curr[instr.in1] * instr.in2;
				possible_ops += r_after == curr;
				
				//Bitwise AND
				//banr
				curr = r_before;
				curr[instr.out] = curr[instr.in1] & curr[instr.in2];
				possible_ops += r_after == curr;
				//bani
				curr = r_before;
				curr[instr.out] = curr[instr.in1] & instr.in2;
				possible_ops += r_after == curr;
				
				//Bitwise OR
				//borr
				curr = r_before;
				curr[instr.out] = curr[instr.in1] | curr[instr.in2];
				possible_ops += r_after == curr;
				//bori
				curr = r_before;
				curr[instr.out] = curr[instr.in1] | instr.in2;
				possible_ops += r_after == curr;
				
				//Assignment
				//setr
				curr = r_before;
				curr[instr.out] = curr[instr.in1];
				possible_ops += r_after == curr;
				//seti
				curr = r_before;
				curr[instr.out] = instr.in1;
				possible_ops += r_after == curr;
				
				//Greater-than testing
				//gtir
				curr = r_before;
				curr[instr.out] = instr.in1 > curr[instr.in2];
				possible_ops += r_after == curr;
				//gtri
				curr = r_before;
				curr[instr.out] = curr[instr.in1] > instr.in2;
				possible_ops += r_after == curr;
				//gtrr
				curr = r_before;
				curr[instr.out] = curr[instr.in1] > curr[instr.in2];
				possible_ops += r_after == curr;
				
				//Equality testing
				//eqir
				curr = r_before;
				curr[instr.out] = instr.in1 == curr[instr.in2];
				possible_ops += r_after == curr;
				//eqri
				curr = r_before;
				curr[instr.out] = curr[instr.in1] == instr.in2;
				possible_ops += r_after == curr;
				//eqrr
				curr = r_before;
				curr[instr.out] = curr[instr.in1] == curr[instr.in2];
				possible_ops += r_after == curr;
				
				geq3_possible_ops += possible_ops >= 3;
		}else{
			reading = false;
		}
	}
	
	std::cout << geq3_possible_ops << std::endl;
	
	return 0;
}