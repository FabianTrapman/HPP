/* masterWorker.cpp
 * ... illustrates the master-worker pattern in OpenMP
 *
 * Compile with -fopenmp, link with -lomp where needed
 *
 * Exercise:
 * - Compile and run as is.
 * - Uncomment #pragma directive, re-compile and re-run
 * - Compare and trace the different executions.
 */
#include <iostream>
#include <omp.h>   // OpenMP

using std::cout, std::endl;

int main()
{
    int id = -1, numThreads = -1;

    cout << endl;

#pragma omp parallel private(id, numThreads)
    {
        id = omp_get_thread_num();
        numThreads = omp_get_num_threads();

        if (id == 0)
        { // thread with ID 0 is master
            cout << "Greetings from the master, # " + std::to_string(id)
                 + " of " + std::to_string(numThreads) + " threads\n";
        }
        else
        { // threads with IDs > 0 are workers
            cout << "Greetings from a worker, # " + std::to_string(id)
                 + " of " + std::to_string(numThreads) + " threads\n";
        }
    }

    cout << endl;

    return 0;
}