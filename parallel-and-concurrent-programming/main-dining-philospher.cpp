//
//  main-dining-philospher.cpp
//  parallel-and-concurrent-programming
//
//  Created by Siddharth Bhasin on 31/10/20.
//

#include <thread>
#include <mutex>

int sushi_count = 5000;

void philosopher(std::mutex &first_chopstick, std::mutex &second_chopstick) {
    while (sushi_count > 0) {
        std::scoped_lock lock(first_chopstick, second_chopstick);
        if (sushi_count) {
            sushi_count--;
        }
    }
}

void main_dining_philospher() {
    std::mutex chopstick_a, chopstick_b;
    std::thread barron(philosopher, std::ref(chopstick_a), std::ref(chopstick_b));
    std::thread olivia(philosopher, std::ref(chopstick_b), std::ref(chopstick_a));
    barron.join();
    olivia.join();
    printf("The philosophers are done eating.\n");
}
