#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>

enum EventType{
	et_Unknown = 0,
	et_BeginShift = 1,
	et_FallsAsleep = 2,
	et_WakesUp = 3,
};

struct TimeRecord{
	unsigned year;
	unsigned month;
	unsigned day;
	unsigned hour;
	unsigned minute;
	EventType event;
	unsigned guard_id;
	
	TimeRecord() :
		year(0),
		month(0),
		day(0),
		hour(0),
		minute(0),
		event(et_Unknown),
		guard_id(0){
	}
	
	operator < (const TimeRecord& other){
		if(year != other.year) return year < other.year;
		if(month != other.month) return month < other.month;
		if(day != other.day) return day < other.day;
		if(hour != other.hour) return hour < other.hour;
		return minute < other.minute;
	}
	
	void print(){ //for debugging
		std::cout << '[' << 
			year << '-' << 
			month << '-' << 
			day << " " << 
			hour << ':' << 
			minute << "] " << 
			event;
		if(event == et_BeginShift) std::cout << " #" << guard_id;
		std::cout << std::endl;
	}
};

struct Guard{
	unsigned sleep_time;
	unsigned sleep_min[60];
	Guard() : sleep_time(0){
		std::memset(sleep_min, 0, sizeof(sleep_min));
	}
};

int main(int argc, char* argv[]){
	std::vector<TimeRecord> input;
	input.reserve(2000);//roughly expected input size
	{
		TimeRecord rec;
		
		std::string word1;
		char pad;
		while(
			std::cin >> pad >>
			rec.year >> pad >>
			rec.month >> pad >>
			rec.day >> pad >>
			rec.hour >> pad >>
			rec.minute >> pad >>
			word1){
			if(word1.empty()) continue;
			switch(word1[0]){
				case 'G': //Guard
					rec.event = et_BeginShift;
					if(!(std::cin >> pad >> rec.guard_id)) continue;
					break;
				case 'f': //falls
					rec.event = et_FallsAsleep;
					break;
				case 'w': //wakes
					rec.event = et_WakesUp;
					break;
				default: //unknown string
					continue;
			}
			std::cin.ignore(512, '\n');
			input.push_back(rec);
		}
	}
	
	std::sort(input.begin(), input.end());
	
	std::map<unsigned, Guard> guards;
	unsigned curr_guard = 0;
	unsigned curr_min = 0;
	bool awake = true;
	
	for(int i = 0; i < input.size(); ++i){
		TimeRecord& rec = input[i];
		if(rec.event == et_BeginShift){
			curr_guard = rec.guard_id;
			curr_min = 0;
			awake = true;
		}else{
			awake = (rec.event == et_FallsAsleep);
			for(unsigned j = curr_min; j < rec.minute && j < 60; ++j){
				if(!awake) {
					guards[curr_guard].sleep_min[j]++;
					guards[curr_guard].sleep_time++;
				}
			}
			curr_min = rec.minute;
		}
	}
	
	unsigned guard_id = 0;
	{
		unsigned max_sleep = 0;
		std::map<unsigned, Guard>::const_iterator it;
		for(it = guards.begin(); it != guards.end(); ++it){
			if(it->second.sleep_time > max_sleep){
				max_sleep = it->second.sleep_time;
				guard_id = it->first;
			}
		}
	}
	
	Guard& sleepy_guard = guards[guard_id];
	unsigned max_minute = 0;
	unsigned minute_id = 0;
	for(int i = 0; i < sizeof(sleepy_guard.sleep_min)/sizeof(sleepy_guard.sleep_min[0]); ++i){
		if(sleepy_guard.sleep_min[i] > max_minute){
			max_minute = sleepy_guard.sleep_min[i];
			minute_id = i;
		}
	}
	
	std::cout << guard_id*minute_id << std::endl;
	
	return 0;
}