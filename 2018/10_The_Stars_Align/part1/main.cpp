#include <iostream>
//#include <iomanip>
#include <vector>
#include <climits>

struct Point{
	int x;
	int y;
	int v_x;
	int v_y;
};

int main(int argc, char* argv[]){
	std::vector<Point> stars;
	stars.reserve(2000);//roughly expected input size
	{
		Point p;
		p.x = 0;
		p.y = 0;
		p.v_x = 0;
		p.v_y = 0;
		char pad;
		while(std::cin.ignore(10) >> p.x >> pad >> p.y && std::cin.ignore(12) >> p.v_x >> pad >> p.v_y && std::cin.ignore(8, '\n')){
			stars.push_back(p);
			//std::cout << "position=<" << std::setw(2) << p.x << ',' << std::setw(3) << p.y << "> velocity=<" << std::setw(2) << p.v_x << ',' << std::setw(3) << p.v_y << '>' << std::endl;
		}
	}
	
	if(stars.empty()) return 1;
	
	int t = 0;
	int last_width = INT_MAX;
	while(++t < 1000000){//limit time to prevent infinite loop
		int min_x = stars[0].x + stars[0].v_x;
		int min_y = stars[0].y + stars[0].v_y;
		int max_x = min_x;
		int max_y = min_y;
		for(unsigned i = 0; i < stars.size(); ++i){
			stars[i].x += stars[i].v_x;
			stars[i].y += stars[i].v_y;
			if(stars[i].x < min_x) min_x = stars[i].x;
			if(stars[i].y < min_y) min_y = stars[i].y;
			if(stars[i].x > max_x) max_x = stars[i].x;
			if(stars[i].y > max_y) max_y = stars[i].y;
		}
		
		int width = (max_x - min_x);
		if(width > last_width){
			//Stars are moving away from each other again
			//Rewind time by one second
			min_x = stars[0].x - stars[0].v_x;
			min_y = stars[0].y - stars[0].v_y;
			max_x = min_x;
			max_y = min_y;
			for(unsigned i = 0; i < stars.size(); ++i){
				stars[i].x -= stars[i].v_x;
				stars[i].y -= stars[i].v_y;
				if(stars[i].x < min_x) min_x = stars[i].x;
				if(stars[i].y < min_y) min_y = stars[i].y;
				if(stars[i].x > max_x) max_x = stars[i].x;
				if(stars[i].y > max_y) max_y = stars[i].y;
			}
			//Print aligned stars
			for(int y = min_y - 2; y <= max_y + 2; ++y){
				for(int x = min_x - 2; x <= max_x + 2; ++x){
					bool found = false;
					for(unsigned i = 0; i < stars.size(); ++i){
						if(x == stars[i].x && y == stars[i].y){
							std::cout << '#';
							found = true;
							break;
						}
					}
					if(!found) std::cout << '.';
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
			break;
		}
		last_width = width;
	}
	
	return 0;
}