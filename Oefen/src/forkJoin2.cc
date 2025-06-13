/* forkJoin2.cpp
 * ... illustrates the fork-join pattern
 *      using multiple OpenMP parallel directives,
 *      and changing the number of threads two ways.
 *
 * Compile with -fopenmp, link with -lomp where needed
 *
 * Exercise:
 * - Compile & run, compare results to source.
 * - Predict how many threads will be used in 'Part IV'?
 * - Uncomment 'Part IV', recompile, rerun.
 */
#include <iostream>
#include <omp.h>   // OpenMP

using std::cout, std::endl;

int main()
{
    cout << "\nBeginning\n";
#pragma omp parallel
    cout << "\nPart I";
    cout << "\n\nBetween I and II...\n";
    omp_set_num_threads(3);
#pragma omp parallel
    cout << "\nPart II...";
    cout << "\n\nBetween II and III...\n";
#pragma omp parallel num_threads(5)
    cout << "\nPart III...";

    cout << "\n\nBetween III and IV...\n";
#pragma omp parallel
    cout << "\nPart IV...";

    cout << "\n\nEnd\n\n";
    return 0;
}