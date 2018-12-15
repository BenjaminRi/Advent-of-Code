#include <iostream>
#include <string>
#include <cstring>

int main(int argc, char* argv[]){
	int cnt_2 = 0;
	int cnt_3 = 0;
	{
		std::string current;
		while(std::cin >> current){
			int ascii_cnt[127];
			std::memset(ascii_cnt, 0, sizeof(ascii_cnt));
			const char* it = current.c_str();
			while(*it){
				if(*it >= 0 && *it < sizeof(ascii_cnt)/sizeof(ascii_cnt[0])){
					ascii_cnt[*it]++;
				}
				it++;
			}
			int done_2 = false;
			int done_3 = false;
			for(unsigned i = 'a'; i <= 'z'; ++i){
				if(ascii_cnt[i] == 2 && !done_2) {
					cnt_2++;
					done_2 = true;
				}
				if(ascii_cnt[i] == 3 && !done_3) {
					cnt_3++;
					done_3 = true;
				}
			}
		}
	}
	
	std::cout << cnt_2*cnt_3 << std::endl;
	
	return 0;
}