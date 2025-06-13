// #include <iostream>
// using namespace std;

// int gen14() {return 14;};

// void print_by_value(int val) {
//     cout << "Value: " << val << endl;
// }

// void print_by_reference_lvalue(int& val) {
//     cout << "Reference to lvalue: " << val << endl;
// }

// int main() {
//     int fourteen = 14;

//     // Functie ontvangt een kopie van de variabele
//     // Dit betekent dat de functie de originele variabele niet aan kan passen
//     // pro : veiligheid, dus originele data blijf onaangetast
//     // con : Kan inefficiënt zijn bij grote objecten
//     print_by_value(14);
//     print_by_value(gen14());
//     print_by_value(fourteen);


//     // Functie ontvangt een referentie van de originele variabele
//     // Dit betekent dat de functie de originele data aan kan passen
//     // pro : efficiënt
//     // con : gevaarlijk, kan de originele data aanpassen
//     // print_by_reference_lvalue(14); // Hier ontstaat een uitzondering omdat 14 geen variabele is
//     // print_by_reference_lvalue(gen14()); // Hetzelfde hier
//     print_by_reference_lvalue(fourteen);



// }

#include <iostream>
#include <thread>
#include <vector>
#include "include/FakeDatabase.hpp"

using namespace std;

int main() {
    FakeDatabase database;

    cout << "testing update. starting value is " << database.get_value() << endl;


    thread thread1(&FakeDatabase::update, &database, 1);
    this_thread::sleep_for(chrono::milliseconds(10));
    thread thread2(&FakeDatabase::update, &database, 2);

    thread1.join();
    thread2.join();

    cout << "testing update. ending value is " << database.get_value() << endl;

    return 0;
}