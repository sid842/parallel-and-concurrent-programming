//
//  main.cpp
//  parallel-and-concurrent-programming
//
//  Created by Siddharth Bhasin on 31/10/20.
//

//Race condition

#include <thread>

unsigned int count = 0;

void shopper() {
	for(int i = 0; i < 1000000; ++i)
		count++; // Read->Modify->Write
}

int main() {
	std::thread t1(shopper);
	std::thread t2(shopper);
	
	t1.join();
	t2.join();
	
	printf("The current count is %d\n", count);
}
