#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void thread_function(string name) {
    cout << "Thread " << name << " is starting" << endl;
    this_thread::sleep_for(chrono::milliseconds(2000)); // Sleep for 2 seconds
    cout << "Thread " << name << " is ending" << endl;
}

int main() {
    vector<thread> threads;
    size_t i;

    for (i = 0; i < 3; i++) {

        cout << "Main before creating thread" << i << endl;
        threads.push_back(thread(thread_function, "thread" + to_string(i)));
    }


    for (i = 0; i < 3; i++) {
        cout << "Main before joining thread " << i << endl;
        threads[i].join();
        cout << "Main : thread " << i << " done" << endl;
    }
    
    return 0;
}

// Wanneer je het programma runned zonder line 18 word de thread niet uitgevoerd.
// Wanneer je het programma runned met line 18 word de thread wel uitgevoerd.
// Het aanmaken van het object van een thread betekent niet dat de thread ook daadwerkelijk runned.

// Het lijkt erop dat wanneer we meerdere threads hebben dat als we de eerste thread
// joinen dat de andere threads ook joinen. Dit komt omdat de threads in de vector
// worden opgeslagen en wanneer we de eerste thread joinen de andere threads ook joinen.