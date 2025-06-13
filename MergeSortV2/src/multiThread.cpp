#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <random>
#include <algorithm> 
#include <chrono>

using namespace std;
using namespace std::chrono;
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

vector<vector<int>> splitList(const vector<int>& vec, int n) {
    vector<vector<int>> result;
    if (n <= 0) return result; // Handle edge case
    
    int chunkSize = vec.size() / n;
    int remainder = vec.size() % n;
    
    auto it = vec.begin();
    for (int i = 0; i < n; ++i) {
        int currentChunkSize = chunkSize + (i < remainder ? 1 : 0);
        result.emplace_back(it, it + currentChunkSize);
        it += currentChunkSize;
    }
    
    return result;
}

vector<int> generate_random_list(int length, int minValue = 0, int maxValue = 100) {
    vector<int> random_list;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(minValue, maxValue);

    for (int i = 0; i < length; ++i) {
        random_list.push_back(dis(gen));
    }

    return random_list;
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

vector<int> threaded_mergesort(vector<int> unsorted_array, int numThreads) {
    // Neemt een ongesorteerde lijst en retourneert een gesorteerde lijst
    // door de MergeSort-methode te gebruiken

    vector<vector<int>> unsorted_2Darray = splitList(unsorted_array, numThreads);

    std::vector<std::future<std::vector<int>>> futures; // Store futures for retrieval
    std::vector<std::thread> threads; // Store thread objects

    for (int i = 0; i < numThreads; ++i) {
        std::packaged_task<std::vector<int>(std::vector<int>)> task(mergesort);
        futures.push_back(task.get_future()); // Store the future
        
        // Start a new thread
        threads.emplace_back(std::move(task), unsorted_2Darray[i]); // Each thread starts at i*10
    }

    // Join all threads
    for (auto& t : threads) {
        t.join();
    }

    // Collect results
    for (int i = 0; i < numThreads; ++i) {
        unsorted_2Darray[i] = futures[i].get(); // Retrieve and store result
    }

    // Combineer de lijsten in de 2D array totdat er slechts één lijst over is
    while (numThreads > 1) {

        vector<vector<int>> temp_2Darray;

        for (int i = 0; i < numThreads; i += 2) {
            temp_2Darray.push_back(combine_lists(unsorted_2Darray[i], unsorted_2Darray[i + 1]));
        }

        unsorted_2Darray = temp_2Darray;
        numThreads = numThreads / 2;
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

// Function to collect timing data for various input sizes
vector<vector<int>> timing_data(vector<int> ns, int runs, int numThreads) {
    vector<vector<int>> times; // Vector to store timing results

    for (int input_size : ns) {

        int total = 0;
        vector<int> gen = generate_random_list(input_size);

        for (int i = 0; i < runs; i++) {
            // Generate a random vector of size `n`

            // Start timing
            steady_clock::time_point begin = steady_clock::now();

            // Sort the vector using BucketSort
            threaded_mergesort(gen, numThreads);

            // Stop timing
            steady_clock::time_point end = steady_clock::now();

            // Calculate time in microseconds
            int time_ms = duration_cast<microseconds>(end - begin).count();
            total += time_ms;
        }

        // Store the average time for this input size
        times.push_back({input_size, total / runs});
    }

    return times;
}

void test_mergesort() {
    // vector<int> test1 = {5, 3, 8, 4, 2};
    // vector<int> result1 = mergesort(test1);
    // cout << "Test 1: ";
    // print_vector(result1);

    vector<int> test2 = generate_random_list(64);
    cout << "Unsorted list: " << endl;
    print_vector(test2);
    cout << endl;

    vector<int> result2 = threaded_mergesort(test2, 8);
    cout << "Sorted list: " << endl;
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

// int main() {
//     test_mergesort();
//     return 0;
// }

int main() {

    vector<int> ns = {50, 100, 500, 1000, 5000, 10000};

    int runs = 100; // Number of runs for each input size

    // Collect timing data for the input sizes
    vector<vector<int>> times8 = timing_data(ns, runs, 1);

    // Output the timing data
    for (vector<int> time : times8) {
        cout << time[0] << ", " << time[1] << endl; // Print input size and average time
    }

    return 0;
}

