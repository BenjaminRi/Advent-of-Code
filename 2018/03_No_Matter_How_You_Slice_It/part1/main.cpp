#include <iostream>
#include <cstring>

int main(int argc, char* argv[]){
	const int rows = 1000;
	const int cols = 1000;
	unsigned char* area = new unsigned char[cols*rows];
	std::memset(area, 0, sizeof(area[0])*cols*rows);
	
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
			
			for(unsigned i = x_offset; i < x_offset + width; ++i){
				for(unsigned j = y_offset; j < y_offset + height; ++j){
					const unsigned idx = i+j*cols;
					if(area[idx] < 2) ++area[idx];
				}
			}
		}
	}
	
	{
		int total = 0;
		for(unsigned i = 0; i < rows; ++i){
			for(unsigned j = 0; j < cols; ++j){
				const unsigned idx = i+j*cols;
				if(area[idx] == 2) ++total;
			}
		}
		std::cout << total << std::endl;
	}
	
	delete[] area;
	
	return 0;
}