/* arraySum.cpp uses an array to sum the values in an input file,
 *  whose name is specified on the command-line.
 */
#include <iostream>
#include <fstream>
#include <omp.h> // OpenMP

using std::cout, std::endl;

void readArray(char *fileName, double **a, int *n);
double sumArray(double *a, int numValues);

int main(int argc, char *argv[])
{
    int howMany;
    double *a;

    if ()

    if (argc != 2)
    {
        cout << endl << "*** Usage: arraySum <numThreads> <inputFile>" << endl << endl;
        exit(1);
    }

    // Set the number of threads
    omp_set_num_threads(atoi(argv[1]));

    double start = omp_get_wtime();
    double result = 0.0;

#pragma omp parallel
    {
        // Master thread reads the array
#pragma omp single
        {
            cout << "The master thread is reading the array" << endl;
            readArray(argv[2], &a, &howMany);
        }

        // Parallel summation
#pragma omp for reduction(+:result)
        for (int i = 0; i < howMany; i++)
        {
            result += a[i];
        }
    }

    double end = omp_get_wtime();

    cout << "The sum of the values in the input file '" << argv[2] << "' is " << result << endl;
    cout << "Elapsed time = " << (end - start) << " sec" << endl;

    free(a);

    return 0;
}

void readArray(char *fileName, double **a, int *n)
{
    int count, howMany;
    double *tempA;
    std::ifstream fin(fileName);
    if (!fin.is_open())
    {
        cout << endl << "*** Unable to open input file '" << fileName << "'" << endl << endl;
        exit(1);
    }

    fin >> howMany;
    tempA = (double *)calloc(howMany, sizeof(double));
    if (tempA == NULL)
    {
        cout << endl << "*** Unable to allocate " << howMany << "-length array" << endl << endl;
        exit(1);
    }

    for (count = 0; count < howMany; count++)
        fin >> tempA[count];

    fin.close();

    *n = howMany;
    *a = tempA;
}

/* sumArray sums the values in an array of doubles.
 * Receive: a, a pointer to the head of an array;
 *          numValues, the number of values in the array.
 * Return: the sum of the values in the array.
 */

double sumArray(double *a, int numValues)
{
    int i;
    double result = 0.0;

    for (i = 0; i < numValues; i++)
    {
        result += a[i];
    }

    return result;
}