#ifndef SOLVERS_HPP
#define SOLVERS_HPP

using namespace std;

void power_method_deflation(int n, double **matrix, double *eigenvalores, double ** eigenvectores, int max_iterations, int num_eigenvalues, double epsilon);                    

#endif