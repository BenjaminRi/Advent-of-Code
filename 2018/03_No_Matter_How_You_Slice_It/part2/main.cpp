#include <iostream>
#include <cstring>
#include <set>

int main(int argc, char* argv[]){
	const int rows = 1000;
	const int cols = 1000;
	//Note: Only works with 1-indexed claims up to 65535
	unsigned short* area = new unsigned short[cols*rows];
	std::memset(area, 0, sizeof(area[0])*cols*rows);
	
	std::set<int> claim_list;
	{
		unsigned claim_id = 0;
		unsigned x_offset = 0;
		unsigned y_offset = 0;
		unsigned width = 0;
		unsigned height = 0;
		char pad;
		while(std::cin >> pad >> claim_id >> pad >> x_offset >> pad >> y_offset >> pad >> width >> pad >> height){
			//std::cout << '#' << claim_id << " @ " << x_offset << ',' << y_offset << ": " << width << 'x' << height << std::endl;
			if(x_offset >= cols) continue;
			if(y_offset >= rows) continue;
			if(x_offset + width > cols) width = cols - x_offset;
			if(y_offset + height > rows) height = rows - y_offset;
			
			claim_list.insert(claim_id);
			
			for(unsigned i = x_offset; i < x_offset + width; ++i){
				for(unsigned j = y_offset; j < y_offset + height; ++j){
					const unsigned idx = i+j*cols;
					if(area[idx] == 0) {
						area[idx] = claim_id;
					}else{
						claim_list.erase(claim_id);
						claim_list.erase(area[idx]);
					}
				}
			}
		}
	}
	
	if(claim_list.size() == 1){
		std::cout << *claim_list.begin() << std::endl;
	}
	
	delete[] area;
	
	return 0;
}