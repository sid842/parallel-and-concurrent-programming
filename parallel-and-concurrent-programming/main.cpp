//
//  main.cpp
//  parallel-and-concurrent-programming
//
//  Created by Siddharth Bhasin on 31/10/20.
//

#include <thread>
#include <mutex>
#include <chrono>

unsigned int count = 0;
std::mutex pencil;

void shopper() {
	
	for(int i = 0; i < 5; ++i) {
		printf("Shopper %d is thinking...\n", std::this_thread::get_id());
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		pencil.lock();
		//Critical section
		count++; // Read->Modify->Write
		pencil.unlock();
	}
}

int main() {
	std::thread t1(shopper);
	std::thread t2(shopper);
	
	t1.join();
	t2.join();
	
	printf("The current count is %d\n", count);
}
