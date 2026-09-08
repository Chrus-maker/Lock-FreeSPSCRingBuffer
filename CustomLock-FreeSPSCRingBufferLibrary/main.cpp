#include <iostream>
#include <vector>
#include <atomic>
#include <thread>
//the combination of release and acquire are like the equailvilant of using std::mutex
//need to add the conveyor ring buffer
using namespace std::literals::chrono_literals;

constexpr int Buffer_Size = 10;
static std::vector<int> buffer(Buffer_Size);
static std::atomic<bool> ready1{false};
static std::atomic<bool> ready2{false};
static bool play = false;
static std::atomic<int> producer_pos{0};
static std::atomic<int> consumer_pos{0};
static int j;


void Producer() {

    for (int i = 0; i <= 20; ++i) {
        int current_producer_pos = producer_pos.load(std::memory_order_relaxed);
        int next_producer_pos = (current_producer_pos + 1) % Buffer_Size;

        while (next_producer_pos == consumer_pos.load(std::memory_order_acquire)) {
            std::this_thread::yield();
        }
        buffer[current_producer_pos] = i;
        std::cout << "Wrote" << i << std::endl;

        producer_pos.store(next_producer_pos, std::memory_order_release);

        std::this_thread::sleep_for(std::chrono::milliseconds(100ms));
    }

}
void Consumer() {
    for (int j = 0; j <= 20; ++j) {
        int current_consumer_pos = consumer_pos.load(std::memory_order_relaxed);

        while (current_consumer_pos == producer_pos.load(std::memory_order_acquire)) {
            std::this_thread::yield();
        }
        int val = buffer[current_consumer_pos] = j;
        std::cout << "Read" << val << std::endl;

        int next_consumer_pos = (current_consumer_pos + 1) % Buffer_Size;

        consumer_pos.store(next_consumer_pos, std::memory_order_release);
    }
}

int main() {

        std::thread t1(Producer);
        std::thread t2(Consumer);

        t1.join();
        t2.join();

}