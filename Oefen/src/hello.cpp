#include <iostream>
#include <omp.h>   // OpenMP

using std::cout, std::endl;

// int main(int argc, char **argv)
// {

//  int num = omp_get_num_threads();

// #pragma omp parallel num_threads(num)
//     {
//     cout << "Hello world!" << endl;
//     }

//     return 0;
// }

int main()
{

    int var = 5;

#pragma omp parallel private(var)
    {
    var = var + omp_get_thread_num();

    cout << "Hello World from thread: " + std::to_string(omp_get_thread_num()) + ", var is " + std::to_string(var) + "\n";    
    }

    return 0;
}