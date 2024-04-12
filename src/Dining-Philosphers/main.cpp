#include <mutex>
#include <thread>
#include <iostream>
#include <vector>
#include <shared_mutex>

struct Table
{
    std::vector<std::mutex> chopsticks;
    Table(int n) : chopsticks(n) {} 
};

class Philospher
{
    int id;
    int left_chopstick;
    int right_chopstick;
    Table& table;
    std::thread t;
public:
    Philospher(int _id, int _left_chopstick, int _right_chopstick, Table& _table)
        : id(_id), left_chopstick(_left_chopstick), right_chopstick(_right_chopstick), table(_table)
    {
    }
    

    void dine() noexcept
    {
        t = std::thread(&Philospher::life, this);
    }

    void life() noexcept
    {
        while (true)
        {
            think();
            eat();
        }
    }

    void think() noexcept
    {
        std::cout << "Philospher [" << id << "] is thinking." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    void eat() noexcept
    {
        std::unique_lock<std::mutex> lock_left(table.chopsticks[left_chopstick], std::defer_lock);
        std::unique_lock<std::mutex> lock_right(table.chopsticks[right_chopstick], std::defer_lock);

        lock(lock_left, lock_right);

        std::cout << "Philospher [" << id << "] is eating." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    void join() noexcept
    {
        t.join();
    }
};

int main()
{
    const int num_philosphers = 5;
    Table table(num_philosphers);
    std::vector<Philospher> philosphers;

    for (size_t i = 0; i < num_philosphers; i++)
    {
        philosphers.emplace_back(i, i, i + 1, table);
    }

    for (auto& philospher: philosphers)
    {
        philospher.dine();
    }

    for (auto& philospher: philosphers)
    {
        philospher.join();
    }
    
    return 0;
}