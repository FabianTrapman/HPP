#include <thread>
#include <mutex>

class FakeDatabase {
    private:
        int value;
    public:
        FakeDatabase();
        void update(int number);
        int get_value();
        std::mutex db_mutex;
};