#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void merge(vector<int>& array, int links, int mid, int rechts) {
    // Bepaal de grootte van de linker en rechter array
    int L = mid - links + 1;
    int R = rechts - mid;

    // Maak alvast twee lege arrays aan
    vector<int> linkerArray(L), rechterArray(R);

    // Vul de arrays met getallen
    copy(array.begin() + links, array.begin() + links + L, linkerArray.begin());
    copy(array.begin() + mid + 1, array.begin() + mid + 1 + R, rechterArray.begin());

    // Vergelijk elk getal aan het begin van elke lijst
    // Voeg het kleinste getal toe aan de uiteindelijke array
    int i = 0, j = 0, k = links;
    while (i < L && j < R) {
        if (linkerArray[i] <= rechterArray[j]) {
            array[k++] = linkerArray[i++];
        } else {
            array[k++] = rechterArray[j++];
        }
    }


    // Voeg het laatste getalletje toe
    while (i < L) {
        array[k++] = linkerArray[i++];
    }

    while (j < R) {
        array[k++] = rechterArray[j++];
    }
}

void mergeSort(vector<int>& array) {
    int n = array.size();

    for (int currSize = 1; currSize < n; currSize *= 2) {
        // Zoek de punten waar de linker en rechter array eindigen en het middelpunt

        for (int links = 0; links < n - 1; links += 2 * currSize) {
            int mid = min(links + currSize - 1, n - 1);
            int rechts = min(links + 2 * currSize - 1, n - 1);

            // De twee arrays worden bijgehouden als [links...mid] en [mid...rechts]
            merge(array, links, mid, rechts);
        }
    }
}

int main() {
    vector<int> array = {53, 21, 8, 45, 72, 36, 90, 15, 62, 77, 29, 5, 48, 39, 84, 17, 3, 66, 11, 54};

    cout << "oorspronkelijke array: ";
    for (int num : array) {
        cout << num << " ";
    }

    mergeSort(array);

    cout << "\ngesorteerde array: ";
    for (int num : array) {
        cout << num << " ";
    }

    return 0;
}


