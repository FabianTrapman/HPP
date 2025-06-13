/* spmd.cpp
 * ... illustrates the SPMD pattern in OpenMP,
 * 	using the commandline arguments
 *      to control the number of threads.
 *
 * Compile with -fopenmp, link with -lomp where needed
 *
 * Exercise:
 * - Compile & run with no commandline args
 * - Rerun with different commandline args,
 *    note race condition
 * - Uncomment private clause, recompile,
 *    rerun, compare results
 */
#include <iostream>
#include <omp.h>   // OpenMP

using std::cout, std::endl;

int main(int argc, char **argv)
{
    int id, numThreads;

    cout << endl;
    if (argc > 1)
    {
        omp_set_num_threads(atoi(argv[1]));
    }

#pragma omp parallel private(id)
    {
        id = omp_get_thread_num();
        numThreads = omp_get_num_threads();
        // This is a concatenated string so it will always be output as one
        cout << "Hello from thread " + std::to_string(id) + " of "
                + std::to_string(numThreads) + "\n";
    }

    cout << endl;
    return 0;
}