//
//  main.cpp
//  parallel-and-concurrent-programming
//
//  Created by Siddharth Bhasin on 31/10/20.
//

#include <thread>
#include <mutex>
#include <chrono>

std::mutex pencil;
unsigned int items_on_notepad = 0;

void shopper(const char* name) {
	int items_to_add = 0;
	while (items_on_notepad <= 20) {
		if(items_to_add && pencil.try_lock()) {
			items_on_notepad += items_to_add;
			printf("%s added %u item(s) to notepad.\n", name, items_to_add);
			items_to_add = 0;
			std::this_thread::sleep_for(std::chrono::milliseconds(300)); //time writing
			pencil.unlock();
		} else {
			std::this_thread::sleep_for(std::chrono::milliseconds(100)); //time searching
			items_to_add++;
			printf("%s found something else to buy.\n", name);
			
		}
	}
}

int main() {
	auto start = std::chrono::steady_clock::now();
	
	std::thread t1(shopper, "Bob");
	std::thread t2(shopper, "Alice");
	
	t1.join();
	t2.join();
	
	auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()-start).count();
	
	printf("Elapsed time: %.2f seconds\n", elapsed_time/1000.0);
}
