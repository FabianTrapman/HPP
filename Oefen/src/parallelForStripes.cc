/* parallelForStripes.cpp
 * ... illustrates how to make OpenMP map threads to
 *	parallel for-loop iterations in 'stripes' instead of blocks
 *	(use only when not accesssing memory).
 *
 * Compile with -fopenmp, link with -lomp where needed
 *
 * Exercise:
 * - Compile, run, compare output to 'Blocks' version
 */
#include <iostream>
#include <omp.h> // OpenMP

using std::cout, std::endl;

int main(int argc, char **argv)
{
    const int REPS = 8;

    cout << endl;
    if (argc > 1)
    {
        omp_set_num_threads(atoi(argv[1]));
    }

#pragma omp parallel
    {
        int id = omp_get_thread_num();
        int numThreads = omp_get_num_threads();
        int i;
        for (i = id; i < REPS; i += numThreads)
        {
            cout << "Thread " + std::to_string(id) + " performed iteration "
                 + std::to_string(i) + "\n";
        }
    }

    cout << endl;

    return 0;
}
