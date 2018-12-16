#include <iostream>
//#include <iomanip>
#include <vector>

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
	unsigned long long last_area = (-1);//underflow to assign ULLONG_MAX
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
		
		unsigned long long area = (unsigned long long) (max_x - min_x) * (unsigned long long) (max_y - min_y);
		if(area > last_area){
			const int final_time = t - 1;
			std::cout << final_time << std::endl;
			break;
		}
		last_area = area;
	}
	
	return 0;
}