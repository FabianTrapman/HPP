#include <iostream>
using namespace std;

int gen14() {return 14;};

void print_by_value(int val) {
    cout << "Value: " << val << endl;
}

void print_by_reference_lvalue(int& val) {
    cout << "Reference to lvalue: " << val << endl;
}

int main() {
    int fourteen = 14;

    // Functie ontvangt een kopie van de variabele
    // Dit betekent dat de functie de originele variabele niet aan kan passen
    // pro : veiligheid, dus originele data blijf onaangetast
    // con : Kan inefficiënt zijn bij grote objecten
    print_by_value(14);
    print_by_value(gen14());
    print_by_value(fourteen);


    // Functie ontvangt een referentie van de originele variabele
    // Dit betekent dat de functie de originele data aan kan passen
    // pro : efficiënt
    // con : gevaarlijk, kan de originele data aanpassen
    // print_by_reference_lvalue(14); // Hier ontstaat een uitzondering omdat 14 geen variabele is
    // print_by_reference_lvalue(gen14()); // Hetzelfde hier
    print_by_reference_lvalue(fourteen);



}