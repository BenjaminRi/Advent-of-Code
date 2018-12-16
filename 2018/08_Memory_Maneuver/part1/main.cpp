#include <iostream>
#include <vector>

struct Node{
	std::vector<Node> children;
	std::vector<int> metadata;
};

void read_recursive(Node& n){
	unsigned num_chld = 0;
	unsigned num_meta = 0;
	std::cin >> num_chld >> num_meta;
	
	n.children.resize(num_chld);
	n.metadata.resize(num_meta);
	
	for(unsigned i = 0; i < num_chld; ++i){
		read_recursive(n.children[i]);
	}
	for(unsigned i = 0; i < num_meta; ++i){
		std::cin >> n.metadata[i];
	}
}

void add_meta(const Node&n, int& sum){
	for(unsigned i = 0; i < n.children.size(); ++i){
		add_meta(n.children[i], sum);
	}
	for(unsigned i = 0; i < n.metadata.size(); ++i){
		sum += n.metadata[i];
	}
}

int main(int argc, char* argv[]){
	Node root_node;
	read_recursive(root_node);
	
	int sum = 0;
	add_meta(root_node, sum);
	
	std::cout << sum << std::endl;
	
	return 0;
}