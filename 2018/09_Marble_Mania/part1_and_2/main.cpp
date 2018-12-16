#include <iostream>
#include <string>
#include <list>
#include <vector>

void move_iter(
	std::list<int>& ring,
	std::list<int>::const_iterator& it,
	int offset){
	if(it != ring.end() && !ring.empty()){
		if(offset > 0){
			while(offset--){
				++it;
				if(it == ring.end()) it = ring.begin();
			}
		}else if(offset < 0){
			while(offset++) {
				if(it == ring.begin()) it = ring.end();
				--it;
			}
		}
	}
}

int main(int argc, char* argv[]){
	unsigned num_players;
	int num_marbles;
	std::string s; //throw away words between numbers
	if(std::cin >> num_players >> s >> s >> s >> s >> s >> num_marbles >> s){
		if(num_players >= 1 && num_marbles >= 1){
			std::vector<long long> players;
			players.resize(num_players);
			
			std::list<int> ring;
			
			int curr_marble = 1;
			ring.push_back(0);
			std::list<int>::const_iterator it = ring.begin();
			while(curr_marble <= num_marbles){
				for(unsigned i = 0; i < players.size(); ++i){
					if(curr_marble % 23 != 0){
						move_iter(ring, it, 2);
						it = ring.insert(it, curr_marble);
					}else{
						players[i] += curr_marble;
						move_iter(ring, it, -7);
						players[i] += *it;
						//it becomes element that follows erased element:
						it = ring.erase(it);
						//make sure it still points to a valid element:
						if(it == ring.end()) it = ring.begin();
					}
					
					curr_marble++;
					if(curr_marble > num_marbles) break;
				}
			}
			long long hi_score = 0;
			for(unsigned i = 0; i < players.size(); ++i){
				if(players[i] > hi_score) hi_score = players[i];
			}
			std::cout << hi_score << std::endl;
			return 0;
		}else{
			return 1;
		}
	}else{
		return 1;
	}
}