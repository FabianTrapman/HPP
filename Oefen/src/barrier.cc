/* barrier.cpp
 * ... illustrates the use of the OpenMP barrier command,
 * 	using the commandline to control the number of threads...
 *
 * Compile with -fopenmp, link with -lomp where needed
 *
 * Exercise:
 * - Compile & run several times, noting interleaving of outputs.
 * - Uncomment the barrier directive, recompile, rerun,
 *   and note the change in the outputs.
 */
#include <iostream>
#include <omp.h>   // OpenMP

using std::cout, std::endl;

int main(int argc, char **argv)
{
    cout << endl;
    if (argc > 1)
    {
        omp_set_num_threads(atoi(argv[1]));
    }

#pragma omp parallel
    {
        int id = omp_get_thread_num();
        int numThreads = omp_get_num_threads();
        cout << "Thread " + std::to_string(id) + " of "
             + std::to_string(numThreads) + " is BEFORE the barrier.\n";

#pragma omp barrier

        cout << "Thread " + std::to_string(id) + " of "
             + std::to_string(numThreads) + " is AFTER the barrier.\n";
    }

    cout << endl;

    return 0;
}
