#include <iostream>
using namespace std;

int gen14() {return 14;};

void print_by_reference_rvalue(const int&& val) {
    cout << "reference to rvalue: " << val << endl;
}

void print_by_const_reference(const int& val) {
    cout << "const reference: " << val << endl;
}

int main() {
    int fourteen = 14;
    
    // Rvalue
    // Met const && wordt een referentie gemaakt naar een tijdelijk object
    print_by_reference_rvalue(14); // Deze wordt verwijdert zodra de functie wordt aangeroepen
    print_by_reference_rvalue(gen14()); // Deze ook
    // print_by_reference_rvalue(fourteen);

    // Lvalue
    // Met const & kan een referentie worden gebruikt zonder de waarde aan te passen
    // Dit is gebruikelijk bij het doorgeven van grote objecten
    print_by_const_reference(14);
    print_by_const_reference(gen14());
    print_by_const_reference(fourteen);
}