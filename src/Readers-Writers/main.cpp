#include <mutex>
#include <thread>
#include <iostream>
#include <vector>
#include <shared_mutex>

constexpr int num_of_readers = 3;
constexpr int num_of_writers = 2;
constexpr int total_operations = num_of_readers + num_of_writers;

class SharedResource
{
    int data;
    std::shared_mutex mtx;
public:
    SharedResource(int value = 0) : data(value) {}
    
    int read() noexcept
    {
        std::shared_lock<std::shared_mutex> lock(mtx);
        return data;
    }

    void write(int value) noexcept
    {
        std::unique_lock<std::shared_mutex> lock(mtx);
        data = value;
    }
};

void reader(SharedResource& resource, const int id) noexcept
{
    for (int i = 0; i < total_operations; i++)
    {
        int value = resource.read();
        std::cout << "Reader [" << id << "] read: " << value << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void writer(SharedResource& resource, const int id) noexcept
{
    for (int i = 0; i < total_operations; i++)
    {
        int value = rand() % 100;
        resource.write(rand() % 100);
        std::cout << "Writer [" << id << "] wrote: " << value << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main()
{
    SharedResource resource;
    std::vector<std::thread> readers;
    std::vector<std::thread> writers;

    for (int i = 0; i < num_of_readers; i++)
    {
        readers.emplace_back(reader, std::ref(resource), i);
    }

    for (int i = 0; i < num_of_writers; i++)
    {
        writers.emplace_back(writer, std::ref(resource), i);
    }

    for (auto& t: readers)
    {
        t.join();
    }

    for (auto& t: writers)
    {
        t.join();
    }
 
    return 0;
}