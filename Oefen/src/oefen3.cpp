#include <iostream>
#include <utility>
using namespace std;



class Move {
    private:
        int value;

    public:
        Move(int value) : value(value) {};
        Move(Move&& rhs) : value(exchange(rhs.value, 0)) {};
        Move clone() const;
        friend ostream& operator<<(ostream& os, Move& m);
};

ostream& operator<<(ostream& os, Move& mm) {
    os << "Mv<" << mm.value << ">";
    return os;
};

Move Move::clone() const {
    return Move(this->value)
};

int main() {
    Move og = Move(3);
    cout << "Original: " << og << endl;

    Move 
}