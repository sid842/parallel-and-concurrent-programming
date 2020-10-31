//
//  main.cpp
//  parallel-and-concurrent-programming
//
//  Created by Siddharth Bhasin on 31/10/20.
//

/**
	Several users reading a calender but only a few users modifying it.
 */

#include <thread>
#include <mutex>
#include <chrono>
#include <array>

char WEEKDAYS[7][10] = {"SUNDAY", "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY"};
int today = 0;
std::mutex marker;

void calender_reader(const int id) {
	for(int i = 0; i < 7; ++i) {
		marker.lock();
		printf("Reader %d sees today as %s.\n", id, WEEKDAYS[today]);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		marker.unlock();
	}
}

void calender_writer(const int id) {
	for(int i = 0; i < 7; ++i) {
		marker.lock();
		today = (today+1)%7;
		printf("Write %d updated today to %s.\n", id, WEEKDAYS[today]);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		marker.unlock();
	}
}

int main() {
	std::array<std::thread, 10> readers;
	for(unsigned int i = 0;  i < readers.size(); ++i)
		readers[i] =  std::thread(calender_reader, i);
		
	std::array<std::thread, 2> writers;
	for(unsigned int i = 0;  i < writers.size(); ++i)
		writers[i] =  std::thread(calender_writer, i);
		
	for(unsigned int i = 0;  i < readers.size(); ++i)
		readers[i].join();
	
	for(unsigned int i = 0;  i < writers.size(); ++i)
		writers[i].join();
}


