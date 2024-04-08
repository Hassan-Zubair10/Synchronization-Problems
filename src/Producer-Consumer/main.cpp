#include <vector>
#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>

constexpr auto items_to_process = 10;

class BoundedBuffer
{
    std::vector<int> buffer;
    size_t front, rear, current_size, max_size;
    std::mutex mtx;
    std::condition_variable not_empty, not_full;
public:
    BoundedBuffer(int size) : buffer(size), front(0), rear(0), max_size(size), current_size(0) {}

    void produce(int value) noexcept
    {
        std::unique_lock<std::mutex> lock(mtx);

        /* If buffer is not full, produce, elsewise wait.*/
        not_full.wait(lock, [this]{ return current_size < max_size; });

        buffer[rear] = value;
        rear = (rear + 1) % max_size;
        current_size += 1;

        lock.unlock();
        not_empty.notify_one();        
    }

    int consume() noexcept
    {
        std::unique_lock<std::mutex> lock(mtx);

        /*If buffer is not empty, wait, elsewise consume.*/
        not_empty.wait(lock, [this]{ return current_size > 0; });

        int value = buffer[front];
        front = (front + 1) % max_size;
        current_size -= 1;

        lock.unlock();
        not_full.notify_one();
        
        return value;
    }
};

void producer(BoundedBuffer& buffer) noexcept
{
    for (size_t i = 0; i < items_to_process; i++)
    {
        std::cout << "Produced: " << i << std::endl;
        buffer.produce(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }    
}

void consumer(BoundedBuffer& buffer) noexcept
{
    for (size_t i = 0; i < items_to_process; i++)
    {
        int value = buffer.consume();
        std::cout << "Consumed: " << value << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
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