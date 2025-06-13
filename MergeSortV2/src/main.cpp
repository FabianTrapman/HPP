#include <iostream>
#include <vector>
using namespace std;


void print_vector(const vector<int>& vec) {
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;
}

void print_2Dvector(const vector<vector<int>>& vec) {
    for (vector<int> inner_vec : vec) {
        for (int num : inner_vec) {
            cout << num << " ";
        }
        cout << endl;
    }
}

vector<int> extend_list(vector<int> unsorted_array) {
    // Neemt een ontoepasselijke lijst voor MergeSort en voegt INT_MAX toe aan het einde
    // om de lijst te verlengen tot een macht van 2
    int size = unsorted_array.size();

    // Als de lijst al een macht van 2 is, retourneer deze dan ongewijzigd
    if ((size & (size - 1)) == 0) {
        return unsorted_array;
    }

    // Zoek de volgende macht van 2
    unsigned int power = 1;
    while (power < size) {
        power <<= 1;
    }

    int difference = power - size;

    // Voeg INT_MAX toe aan het einde van de lijst
    for (int i = 0; i < difference; i++) {
        unsorted_array.push_back(INT_MAX);
    }

    return unsorted_array;

}

vector<int> combine_lists(vector<int> unsorted_array1, vector<int> unsorted_array2) {
    // Neemt twee lijsten en combineert ze op de MergeSort manier
    // Dus de eerste twee getallen van elke lijst worden vergeleken met elkaar


    int total_size = unsorted_array1.size() + unsorted_array2.size();
    vector<int> sorted_array;


    for (int i = 0; i < total_size; i++) {

        // Als een van de lijsten leeg is, voeg dan de rest van de andere lijst toe aan de gesorteerde lijst
        if (unsorted_array1.size() == 0) {
            sorted_array.insert(sorted_array.end(), unsorted_array2.begin(), unsorted_array2.end());
            break;
        }
        else if (unsorted_array2.size() == 0) {
            sorted_array.insert(sorted_array.end(), unsorted_array1.begin(), unsorted_array1.end());
            break;
        }
        else if (unsorted_array1[0] > unsorted_array2[0]) {
            sorted_array.push_back(unsorted_array2[0]);
            unsorted_array2.erase(unsorted_array2.begin());
        }
        else if (unsorted_array1[0] < unsorted_array2[0]) {
            sorted_array.push_back(unsorted_array1[0]);
            unsorted_array1.erase(unsorted_array1.begin());
        }
        else if (unsorted_array1[0] == unsorted_array2[0]) {
            sorted_array.push_back(unsorted_array1[0]);
            unsorted_array1.erase(unsorted_array1.begin());
        }
    }

    return sorted_array;

}

vector<int> mergesort(vector<int> unsorted_array) {
    // Neemt een ongesorteerde lijst en retourneert een gesorteerde lijst
    // door de MergeSort-methode te gebruiken


    // Wanneer de lijst niet een macht van 2 is, voeg INT_MAX toe aan het einde
    int og_size = unsorted_array.size();
    unsorted_array = extend_list(unsorted_array);

    vector<vector<int>> unsorted_2Darray;
    int size = unsorted_array.size();
    int mid = size;

    // Voeg elke waarde van de lijst toe aan een 2D array
    // waarbij elke waarde een aparte lijst is
    for (int num : unsorted_array) {
        vector<int> temp = { num };
        unsorted_2Darray.push_back(temp);
    }


    // Combineer de lijsten in de 2D array totdat er slechts één lijst over is
    while (mid > 1) {

        vector<vector<int>> temp_2Darray;

        for (int i = 0; i < mid; i += 2) {
            temp_2Darray.push_back(combine_lists(unsorted_2Darray[i], unsorted_2Darray[i + 1]));
        }

        unsorted_2Darray = temp_2Darray;
        mid = mid / 2;
    }

    // Haal de gesorteerde lijst uit de 2D array
    vector<int> sorted_array;

    // Voeg alleen de oorspronkelijke waarde toe aan de gesorteerde lijst (geen INT_MAX)
    for (int num : unsorted_2Darray[0]) {
        if (num != INT_MAX) {
            sorted_array.push_back(num);
        }
        else {
            break;
        }
    }



    return sorted_array;
}

void test_mergesort() {
    // vector<int> test1 = {5, 3, 8, 4, 2};
    // vector<int> result1 = mergesort(test1);
    // cout << "Test 1: ";
    // print_vector(result1);

    vector<int> test2 = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    vector<int> result2 = mergesort(test2);
    cout << "Test 2: ";
    print_vector(result2);

    // vector<int> test3 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // vector<int> result3 = mergesort(test2);
    // cout << "Test 3: ";
    // print_vector(result3);

    // vector<int> test4 = {5, 5, 5, 5, 5};
    // vector<int> result4 = mergesort(test4);
    // cout << "Test 4: ";
    // print_vector(result4);

    // vector<int> test5 = {};
    // vector<int> result5 = mergesort(test5);
    // cout << "Test 5: ";
    // print_vector(result5);
}

int main() {
    test_mergesort();
    return 0;

}

