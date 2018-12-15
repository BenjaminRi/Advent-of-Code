#include <iostream>
#include <string>
#include <map>
#include <set>

typedef char id_type;

struct Node{
	id_type id;
	std::set<id_type> dependency;
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
	
	bool changed = false;
	do{
		//infinite loop prevention on circular dependencies:
		changed = false;
		
		for(it = nodes.begin(); it != nodes.end(); ++it){
			bool step_ready = true;
			{
				const Node& n = it->second;
				std::set<id_type>::const_iterator it2;
				for(it2 = n.dependency.begin(); it2 != n.dependency.end(); ++it2){
					if(nodes.find(*it2) != nodes.end()){
						//Still has open dependencies
						step_ready = false;
						break;
					}
				}
			}
			if(step_ready){
				std::cout << it->first;
				nodes.erase(it);
				changed = true;
				break;
			}
		}
	}while(changed);
	
	std::cout << std::endl;
	
	return 0;
}