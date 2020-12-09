#ifndef Files
#define Files
#include <bits/stdc++.h>

using namespace std;

void update_dataset(int images_per_person, int max_index, int rows, int cols, int max_scale, double **A);
void update_PGM(int h, int m, int rows, int cols, int max_scale, double **A);
void update_PGMTest(int h, int m, int rows, int cols, int max_scale, double *A);

void write_PGM(int index, int rows, int cols, int max_scale, double **A);
void write_Individual_PGM(int index, int person, int rows, int cols, int max_scale, double *A);
void write_eigenfaces(int K, int rows, int cols, int max_scale, double **A);
void write_average_face(int rows, int cols, int max_scale, double *A);

double **create_matriz_cero(int n, int m);
double *create_vector_cero(int n);
void write_vector(int n, double *vector, char *vecname);
void write_matrix(int n,int m, double **matrix, char *matrix_name);
void freeMatrix(int n, double ** matrix);

int *set_training_index (int images_per_person, int end_index, int M);
void write_eigengraph(int size, double *x, string filename);

#endif

