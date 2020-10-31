//
//  main.cpp
//  parallel-and-concurrent-programming
//
//  Created by Siddharth Bhasin on 31/10/20.
//

#include <thread>
#include <chrono>

bool chopping = true;

void vegetable_chopper(const char* name) {
	unsigned int vegetable_count = 0;
	while(chopping) {
		vegetable_count++;
	}
	
	printf("%s chopped %u vegetables.\n", name, vegetable_count);
}

int main() {
	std::thread bob(vegetable_chopper, "Bob");
	std::thread alice(vegetable_chopper, "Alice");
	
	printf("Bob and Alice are chopping vegetables...\n");
	
	std::this_thread::sleep_for(std::chrono::seconds(1));
	
	chopping = false;
	bob.join();
	alice.join();
}
