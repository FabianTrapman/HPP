/* forkJoin.cpp
 * ... illustrates the fork-join pattern
 *      using OpenMP's parallel directive.
 *
 * Compile with -fopenmp, link with -lomp where needed
 *
 * Exercise:
 * - Compile & run, uncomment the pragma,
 *    recompile & run, compare results.
 */
#include <iostream>
#include <omp.h>   // OpenMP

using std::cout, std::endl;

int main()
{
    cout << "Before..." << endl;
// #pragma omp parallel
    cout << "During..." << endl;
    cout << endl << "After..." << endl;

    return 0;
}

