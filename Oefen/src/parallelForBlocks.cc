/* parallelForBlocks.cpp
 * ... illustrates the use of OpenMP's default parallel for loop
 *  	in which threads iterate through blocks of the index range
 *	(cache-beneficial when accessing adjacent memory locations).
 *
 * Compile with -fopenmp, link with -lomp where needed
 *
 * Exercise:
 * - Compile, run, trace execution
 */
#include <iostream>
#include <omp.h> // OpenMP

using std::cout, std::endl;

int main(int argc, char **argv)
{
    const int REPS = 8;
    int id, i;

    cout << endl;
    if (argc > 1)
    {
        omp_set_num_threads(atoi(argv[1]));
    }

#pragma omp parallel for private(id, i)
    {
    id = omp_get_thread_num();


    for (i = 0; i < REPS; i++)
    {
        cout << "Thread " + std::to_string(id) + " performed iteration "
             + std::to_string(i) + "\n";
    }

    cout << endl;

    }

    return 0;
}
