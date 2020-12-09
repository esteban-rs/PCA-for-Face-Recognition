#ifndef TOOLS_HPP
#define TOOLS_HPP

using namespace std;

void set_ORL_info(int rows, int cols, int max_scale);
int PCA_Component ();

double *calculate_average(int n, int m, double ** A);
void transpose_matrix(int n, int m, double **matrix, double **matrix_transpose);
void matrix_multiplication(int rows, int pivot, int cols, double **A, double **B, double **C);
void average_contribution(int n, int m, double *V, double **A);
void get_eigenface_matrix (int N, int M, double **A,double **eigenvectors,  double K, double **ET);

void change_interval(int n, int m, double **A);
double distance_vv(int n, double *A, double *B);
double get_max_distance(int n, int m, double **A);

void normal_vector( int n, double *vector);
void product_mv(int n, int m, double **matrix, double *V_0, double *V_1);
void contribuciones(int n, int r, double **eigenvectores, double *V_0);

void eigenplot_gnu(char* name0);

#endif
