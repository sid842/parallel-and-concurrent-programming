//
//  main.cpp
//  parallel-and-concurrent-programming
//
//  Created by Siddharth Bhasin on 31/10/20.
//

#include <thread>
#include <chrono>

bool chopping = true;

void kitchen_cleaner() {
	while(true) {
		printf("Bob cleaned the kitchen.\n");
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

int main() {

	std::thread bob(kitchen_cleaner);
	//Bob now becomes a daemon thread
	bob.detach();
	
	for(int i = 0; i < 3; ++i) {
		printf("Alice is cooking...\n");
		std::this_thread::sleep_for(std::chrono::milliseconds(1500));
	}
	
	printf("Alice is done.\n");
}

//A daemon thread will be abruptly terminated when the main thread finishes. If that occurs during a write operation the file could be corrupted. So use daemon threads carefully.
