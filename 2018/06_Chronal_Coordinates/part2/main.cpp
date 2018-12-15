#include <iostream>
#include <vector>
#include <cmath>

struct Point{
	int x;
	int y;
};

int main(int argc, char* argv[]){
	std::vector<Point> points;
	points.reserve(2000);//roughly expected input size
	
	//Points that span the rectangle in which all points are:
	Point min_coords;
	Point max_coords;
	
	{
		Point point;
		char pad;
		bool first_run = true;
		while(std::cin >> point.x >> pad >> point.y){
			points.push_back(point);
			if(first_run){
				min_coords = point;
				max_coords = point;
				first_run = false;
			}else{
				if(point.x < min_coords.x) min_coords.x = point.x;
				if(point.y < min_coords.y) min_coords.y = point.y;
				if(point.x > max_coords.x) max_coords.x = point.x;
				if(point.y > max_coords.y) max_coords.y = point.y;
			}
		}
	}
	
	//Make sure grid is large enough to capture all points
	min_coords.x -= 50;
	min_coords.y -= 50;
	max_coords.x += 50;
	max_coords.y += 50;
	
	const int exclusion_dist = 10000;
	int safe_cells = 0;
	
	for(int y = min_coords.y; y <= max_coords.y; ++y){
		for(int x = min_coords.x; x <= max_coords.x; ++x){
			int distance_sum = 0;
			for(unsigned i = 0; i < points.size() && distance_sum < exclusion_dist; ++i){
				distance_sum += std::abs(points[i].x - x) + std::abs(points[i].y - y);
			}
			if(distance_sum < exclusion_dist) safe_cells++;
		}
	}
	
	std::cout << safe_cells << std::endl;
	
	return 0;
}