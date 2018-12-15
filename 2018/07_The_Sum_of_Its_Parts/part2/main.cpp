#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>

typedef char id_type;

struct Node{
	id_type id;
	std::set<id_type> dependency;
	
	int duration() const{
		return id - 'A' + 1 + 60;
	}
};

struct Worker{
	id_type current;
	int time_left;
	Worker(){
		current = ' ';
		time_left = 0;
	}
};

int main(int argc, char* argv[]){
	std::map<id_type, Node> nodes;
	{
		std::string line;
		while(std::getline(std::cin, line)){
			if(line.size() > 36){
				const id_type current = line[36];
				const id_type depends = line[5];
				nodes[current].id = current; //insert node (if new)
				nodes[current].dependency.insert(depends);
				nodes[depends].id = depends; //insert node (if new)
			}
		}
	}
	std::map<id_type, Node>::const_iterator it;
	
	std::vector<Worker> workers(5);
	
	bool work_left = false;
	int time = 0;
	do{
		work_left = false;
		std::set<id_type> to_delete;
		
		for(it = nodes.begin(); it != nodes.end(); ++it){
			bool step_ready = true;
			{
				const Node& n = it->second;
				std::set<id_type>::const_iterator sit;
				for(sit = n.dependency.begin(); sit != n.dependency.end(); ++sit){
					if(nodes.find(*sit) != nodes.end()){
						//Still has open dependencies
						step_ready = false;
						break;
					}
					std::vector<Worker>::const_iterator wit;
					for(wit = workers.begin(); wit != workers.end(); ++wit){
						if(wit->current == *sit && wit->time_left > 0){
							//Someone is still working on this step
							step_ready = false;
							break;
						}
					}
				}
			}
			if(step_ready){
				//std::cout << it->first;
				std::vector<Worker>::iterator wit;
				//Find and assign worker for this job (if one is free)
				for(wit = workers.begin(); wit != workers.end(); ++wit){
					if(wit->time_left == 0) {
						wit->current = it->first;
						wit->time_left = it->second.duration();
						to_delete.insert(it->first);
						break;
					}
				}
			}
		}
		while(!to_delete.empty()){
			nodes.erase(*to_delete.begin());
			to_delete.erase(to_delete.begin());
		}
		
		std::vector<Worker>::iterator wit;
		for(wit = workers.begin(); wit != workers.end(); ++wit){
			if(wit->time_left > 0) wit->time_left--;
			if(wit->time_left > 0) work_left = true;
		}
		if(!nodes.empty()) work_left = true;
		
		time++;
	}while(work_left);
	
	std::cout << time << std::endl;
	
	return 0;
}