#include <iostream>
#include <vector>

struct Node{
	std::vector<Node> children;
	std::vector<int> metadata;
	int sum;
	bool sum_cached;
};

void read_recursive(Node& n){
	unsigned num_chld = 0;
	unsigned num_meta = 0;
	std::cin >> num_chld >> num_meta;
	
	n.children.resize(num_chld);
	n.metadata.resize(num_meta);
	n.sum = 0;
	n.sum_cached = false;
	
	for(unsigned i = 0; i < num_chld; ++i){
		read_recursive(n.children[i]);
	}
	for(unsigned i = 0; i < num_meta; ++i){
		std::cin >> n.metadata[i];
	}
}

int calc_sum(Node& n){
	if(!n.sum_cached){
		n.sum = 0;
		if(n.children.empty()){
			for(int i = 0; i < n.metadata.size(); ++i){
				n.sum += n.metadata[i];
			}
		}else{
			for(int i = 0; i < n.metadata.size(); ++i){
				const int idx = n.metadata[i] - 1; //metadata is 1-indexed
				if(idx >= 0 && idx < n.children.size()){
					n.sum += calc_sum(n.children[idx]);
				}
			}
		}
		n.sum_cached = true;
	}
	return n.sum;
}

int main(int argc, char* argv[]){
	Node root_node;
	read_recursive(root_node);
	calc_sum(root_node);
	std::cout << root_node.sum << std::endl;
	return 0;
}