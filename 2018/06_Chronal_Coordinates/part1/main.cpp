#include <iostream>
#include <vector>
#include <cmath>

struct Point{
	int x;
	int y;
};

struct GridCell{
	int owner;
	int dist;
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
	
	const int grid_w = max_coords.x - min_coords.x + 1;
	const int grid_h = max_coords.y - min_coords.y + 1;
	
	GridCell* grid = new GridCell[grid_w * grid_h];
	for(unsigned i = 0; i < grid_w * grid_h; ++i){
		grid[i].owner = -1;
		grid[i].dist = -1;
	}
	
	for(unsigned i = 0; i < points.size(); ++i){
		for(int y = min_coords.y; y <= max_coords.y; ++y){
			for(int x = min_coords.x; x <= max_coords.x; ++x){
				const int curr_dist = std::abs(points[i].x - x) + std::abs(points[i].y - y);
				const int coord = (x-min_coords.x) + grid_w * (y-min_coords.y);
				
				if(grid[coord].dist == -1 || grid[coord].dist > curr_dist){
					//point is closer - becomes owner
					grid[coord].dist = curr_dist;
					grid[coord].owner = i;
				}else if(grid[coord].dist == curr_dist){
					//contested cell - no owner
					grid[coord].owner = -1;
				}
			}
		}
	}
	
	std::vector<int> cell_count;
	cell_count.resize(points.size());
	for(unsigned i = 0; i < grid_w * grid_h; ++i){
		if(grid[i].owner != -1){
			cell_count[grid[i].owner]++;
		}
	}
	for(int y = min_coords.y; y <= max_coords.y; ++y){
		for(int x = min_coords.x; x <= max_coords.x; ++x){
			const int coord = (x-min_coords.x) + grid_w * (y-min_coords.y);
			//std::cout << (char) (grid[coord].owner + 'A');//DEBUG
			if(x == min_coords.x || x == max_coords.x || y == min_coords.y || y == max_coords.y){
				
				//disqualify all areas that touch border
				cell_count[grid[coord].owner] = -1;
			}
		}
		//std::cout << std::endl;//DEBUG
	}
	int max_area = 0;
	for(int i = 0; i < cell_count.size(); ++i){
		if(cell_count[i] > max_area) max_area = cell_count[i];
	}
	
	std::cout << max_area << std::endl;
	
	delete[] grid;
	
	return 0;
}