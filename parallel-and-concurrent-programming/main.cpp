//
//  main.cpp
//  parallel-and-concurrent-programming
//
//  Created by Siddharth Bhasin on 31/10/20.
//

#include <thread>
#include <mutex>

unsigned int count = 0;
std::mutex pencil;

void shopper() {
	pencil.lock();
	//Critical section
	for(int i = 0; i < 1000000; ++i)
		count++; // Read->Modify->Write
		
	pencil.unlock();
}

int main() {
	std::thread t1(shopper);
	std::thread t2(shopper);
	
	t1.join();
	t2.join();
	
	printf("The current count is %d\n", count);
}
