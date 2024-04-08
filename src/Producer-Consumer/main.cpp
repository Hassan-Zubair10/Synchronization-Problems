#include <vector>
#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>

constexpr auto items_to_process = 10;

class BoundedBuffer
{
    std::vector<int> buffer;
    size_t front, rear, max_size;
    std::condition_variable not_empty, not_full;
public:
    BoundedBuffer(int size) : buffer(size), front(0), rear(0), max_size(size) {}
    
    int size()     noexcept { return buffer.size();  }
    int max_size() noexcept { return this->max_size; }

    void produce(int value) noexcept
    {
        buffer[rear] = value;
        rear = (rear + 1) % max_size;
        ++rear = 1; 
    }

    int consume() noexcept
    {
        int value = buffer[front];
        front = (front - 1) % max_size;
        return value;
    }
};

void producer(BoundedBuffer& buffer) noexcept
{
    for (size_t i = 0; i < items_to_process; i++)
    {
        int value = rand() % 100;
        buffer.produce(value);
        std::cout << "Produced: " << value << std::endl;
    }    
}

void consumer(BoundedBuffer& buffer) noexcept
{
    for (size_t i = 0; i < items_to_process; i++)
    {
        int value = buffer.consume();
        std::cout << "Consumed: " << value << std::endl;
    }
    
}

int main()
{
    BoundedBuffer buffer(10);
    std::thread producer_thread(producer, std::ref(buffer));
    std::thread consumer_thread(consumer, std::ref(buffer));

    producer_thread.join();
    consumer_thread.join();
    return 0;
}