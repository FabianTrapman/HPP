#include <iostream>
#include "include/fakedatabase.hpp"

using namespace std;

FakeDatabase::FakeDatabase() {
    value = 1;
}

void FakeDatabase::update(int number) {
    cout << "Thread " << number << ": starting_update" << endl;

    lock_guard<mutex> guard(db_mutex);
    int local_copy = value;
    
    local_copy++;
    this_thread::sleep_for(chrono::milliseconds(100));
    value = local_copy;
    cout << "Thread " << number << ": ending_update" << endl;
}

int FakeDatabase::get_value() {
    return value;
}