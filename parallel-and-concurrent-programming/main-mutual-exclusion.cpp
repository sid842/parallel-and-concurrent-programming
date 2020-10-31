//
//  main-mutual-exclusion.cpp
//  parallel-and-concurrent-programming
//
//  Created by Siddharth Bhasin on 31/10/20.
//

#include <thread>
#include <mutex>
#include <chrono>
#include <atomic>

//unsigned int count = 0;
//std::mutex pencil;

namespace {
//This construct can also help in synchronization.
std::atomic<unsigned int> count{0};

void shopper() {
	
	for(int i = 0; i < 5; ++i) {
		count++; // Read->Modify->Write
	}
}

void main_mutual_exclusion() {
	std::thread t1(shopper);
	std::thread t2(shopper);
	
	t1.join();
	t2.join();
	
	printf("The current count is %d\n", count.load()); //.load
}

}
