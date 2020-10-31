//
//  main.cpp
//  parallel-and-concurrent-programming
//
//  Created by Siddharth Bhasin on 31/10/20.
//

#include <thread>
#include <mutex>

unsigned int garlic_count = 0;
unsigned int potato_count = 0;

std::recursive_mutex pencil;

void add_garlic() {
	pencil.lock();
	garlic_count++;
	pencil.unlock();
}

void add_potato() {
	pencil.lock();
	potato_count++;
	add_garlic();	// Now this would work since it is now recursive_mutex.
	pencil.unlock();
}

void shopper() {
	
	for(int i = 0; i < 10000; ++i) {
		add_garlic();
		add_potato();
	}
}

int main() {
	std::thread t1(shopper);
	std::thread t2(shopper);
	
	t1.join();
	t2.join();
	
	printf("We should buy %d garlic.\n", garlic_count);
	printf("We should buy %d potatoes.\n", potato_count);
}
