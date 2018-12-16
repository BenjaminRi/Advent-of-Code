#include <iostream>

#include <cstring>
#include <string>

#include <map>
#include <set>
#include <vector>

#include <exception>

class Regs{
	public:
		inline int& operator[](const unsigned idx){
			if(idx < sizeof(r)/sizeof(r[0])) return r[idx];
			throw std::invalid_argument("Invalid index");
		}
		inline bool operator==(const Regs& other){
			return !memcmp(r, other.r, sizeof(r));
		}
		inline void clear(){
			std::memset(r, 0, sizeof(r));
		}
	private:
		int r[4];
};

enum Opcode{
	OP_BEGIN,
	addr = OP_BEGIN,
	addi,
	mulr,
	muli,
	banr,
	bani,
	borr,
	bori,
	setr,
	seti,
	gtir,
	gtri,
	gtrr,
	eqir,
	eqri,
	eqrr,
	OP_END,
};

struct Instr{
	Opcode op;
	int in1;
	int in2;
	int out;
};

struct InstrUnknownOp{
	int op;
	int in1;
	int in2;
	int out;
};

struct VirtualMachine{
	VirtualMachine(){
		r.clear();
	}
	VirtualMachine(const Regs& regs){
		r = regs;
	}
	Regs r;
	inline void exec(const Instr& instr){
		exec(instr.op, instr.in1, instr.in2, instr.out);
	}
	void exec(const Opcode op, const int in1, const int in2, const int out){
		switch(op){
			//Addition
			case addr:
				r[out] = r[in1] + r[in2];
				break;
			case addi:
				r[out] = r[in1] + in2;
				break;
			//Multiplication
			case mulr:
				r[out] = r[in1] * r[in2];
				break;
			case muli:
				r[out] = r[in1] * in2;
				break;
			//Bitwise AND
			case banr:
				r[out] = r[in1] & r[in2];
				break;
			case bani:
				r[out] = r[in1] & in2;
				break;
			//Bitwise OR
			case borr:
				r[out] = r[in1] | r[in2];
				break;
			case bori:
				r[out] = r[in1] | in2;
				break;
			//Assignment
			case setr:
				r[out] = r[in1]; //ignore in2
				break;
			case seti:
				r[out] = in1; //ignore in2
				break;
			//Greater-than testing
			case gtir:
				r[out] = in1 > r[in2];
				break;
			case gtri:
				r[out] = r[in1] > in2;
				break;
			case gtrr:
				r[out] = r[in1] > r[in2];
				break;
			//Equality testing
			case eqir:
				r[out] = (in1 == r[in2]);
				break;
			case eqri:
				r[out] = (r[in1] == in2);
				break;
			case eqrr:
				r[out] = (r[in1] == r[in2]);
				break;
			default:
				throw std::invalid_argument("Unknown op");
		}
	}
};

struct Sample{
	Regs r_before;
	Regs r_after;
	InstrUnknownOp instr;
};

bool clear_input(){
	std::cin.clear();
	return false;
}

int main(int argc, char* argv[]){
	std::vector<InstrUnknownOp> program;
	program.reserve(2000);//roughly expected input size
	
	std::vector<Sample> samples;
	samples.reserve(2000);//roughly expected input size
	
	{
		bool reading = true;
		InstrUnknownOp instr;
		Sample sample;
		std::string s;
		char pad;
		while(reading){
			if(std::cin >> instr.op >> instr.in1 >> instr.in2 >> instr.out || clear_input()){
				program.push_back(instr);
			}else if(
				std::cin >> s >> pad >> sample.r_before[0] >> pad >> sample.r_before[1] >> pad >> sample.r_before[2] >> pad >> sample.r_before[3] >> pad >> 
				sample.instr.op >> sample.instr.in1 >> sample.instr.in2 >> sample.instr.out >>
				s >> pad >> sample.r_after[0] >> pad >> sample.r_after[1] >> pad >> sample.r_after[2] >> pad >> sample.r_after[3] >> pad){
					
				samples.push_back(sample);
			}else{
				reading = false;
			}
		}
	}
	
	const unsigned puzzle_part = 2;
	if(puzzle_part == 1){
		int samples_geq3_ops = 0;
		for(unsigned i = 0; i < samples.size(); ++i){
			int possible_ops = 0;
			for(Opcode op = OP_BEGIN; op < OP_END; op = (Opcode) (op + 1)){
				VirtualMachine vm(samples[i].r_before);
				vm.exec(op, samples[i].instr.in1, samples[i].instr.in2, samples[i].instr.out);
				possible_ops += (samples[i].r_after == vm.r);
			}
			samples_geq3_ops += (possible_ops >= 3);
		}
		std::cout << samples_geq3_ops << std::endl;
	}else if(puzzle_part == 2){
		bool changed = true;
		std::map<int, Opcode> op_map;
		std::set<Opcode> ops_done;
		while(changed){
			changed = false;
			for(unsigned i = 0; i < samples.size(); ++i){
				int possible_ops = 0;
				Opcode last_valid_op = OP_END;
				for(Opcode op = OP_BEGIN; op < OP_END; op = (Opcode) (op + 1)){
					if(ops_done.find(op) != ops_done.end()) continue;
					VirtualMachine vm(samples[i].r_before);
					vm.exec(op, samples[i].instr.in1, samples[i].instr.in2, samples[i].instr.out);
					if(samples[i].r_after == vm.r){
						possible_ops++;
						last_valid_op = op;
					}
				}
				if(possible_ops == 1){
					op_map[samples[i].instr.op] = last_valid_op;
					ops_done.insert(last_valid_op);
					changed = true;
					//std::cout << "int: " << samples[i].instr.op << " is op: " << last_valid_op << std::endl;
				}
			}
		}
		VirtualMachine vm;
		for(unsigned i = 0; i < program.size(); ++i){
			Instr instr;
			if(op_map.find(program[i].op) == op_map.end()){
				throw std::invalid_argument("Unknown opcode");
			}
			instr.op = op_map[program[i].op];
			instr.in1 = program[i].in1;
			instr.in2 = program[i].in2;
			instr.out = program[i].out;
			vm.exec(instr);
		}
		std::cout << vm.r[0] << std::endl;
	}
	
	return 0;
}