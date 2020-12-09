#include <bits/stdc++.h>
#include "Files.hpp"
#include "Tools.hpp"

void set_ORL_info(int rows, int cols, int max_scale) {
    cout << "*-- ORL Face Database --*" << endl;
    cout << "PERSONS          : 40    " << endl;
    cout << "IMAGES PER PERSON: 10    " << endl;
    cout << "------- PGM INFO ------- " << endl;
    cout << "ROWS      : " << rows << endl;
    cout << "COLS      : " << cols << endl;
    cout << "MAX SCALE : " << max_scale << endl;
}

int PCA_Component () {
    int K = 0;
    cout << "-------------------------" << endl;
    cout << "320 Images for training" << endl;
    cout << "80 Images for testing" << endl;
    cout << "Number of components [1,320]: ";

    cin >> K;
    return K;
}

double *calculate_average(int n, int m, double **A) {
    double *average = create_vector_cero(m);

    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            average[j] += A[i][j];
        }
        average[j] = average[j]/n;
    }

    return average;
}

void transpose_matrix(int n, int m, double **matrix, double **matrix_transpose){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            matrix_transpose[j][i] = matrix[i][j];
        }
    }
}

void matrix_multiplication(int rows, int pivot, int cols, double **A, double **B, double **C) {
    double suma = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            for (int k = 0; k < pivot; k++ ) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void average_contribution(int n, int m, double *V, double **A) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            A[i][j] -= V[j];
        }
    }
}

void get_eigenface_matrix (int N, int M, double **A,double **eigenvectors,  double K, double **ET) {
    // Extract vector from eigenvectors and multiply 
    double *e = create_vector_cero(M);
    double *Ae = create_vector_cero(N);

    for (int i = 0; i < K; i++) {
        // copy eigenvectors in a vector
        for (int j = 0; j < M; j++) {
            e[j] = eigenvectors[i][j];
        }
        // Save Ae_j in a vector
        product_mv(N, M, A, e, Ae);
        normal_vector(N, Ae);

        // copy result to ET row
        for (int j = 0; j < N; j++) {
            ET[i][j] = Ae[j];
        }
    }

    free(e);
    free(Ae);
}

void normal_vector(int n, double *vector){
    double suma = 0;

    for (int i = 0; i < n; i++){
        suma += vector[i]*vector[i];
    }

    suma = sqrt(suma);
    
    for (int i = 0; i < n; i++){
        vector[i] = vector[i]/suma;
    }
}

void change_interval(int n, int m, double **A) {
    double max = 0;
    double min = 0;
    for (int i = 0; i < n; i++) {
        max = 0;
        min = 1000;
        for (int j = 0; j < m; j++) {
            if (A[i][j] > max) {
                max = A[i][j];
            }
            if (A[i][j] < min) {
                min = A[i][j];
            }
        }

        // change values
        for (int j = 0; j < m; j++) {
            A[i][j] = (A[i][j] - min)/ (max-min);
        }

    }
}

void product_mv(int n, int m, double **matrix, double *V_0, double *V_1){
    for (int i = 0; i < n; i++){
        double suma = 0;
        for (int j = 0; j < m; j++){
                suma += matrix[i][j]*V_0[j];
        }
        V_1[i] = suma;
    }
}

double distance_vv(int n, double *A, double *B) {
    double suma = 0;
    for (int i = 0; i < n; i++) {
        suma += (A[i] - B[i])*(A[i] - B[i]);
    }

    suma = sqrt(suma);

    return suma;
}

double get_max_distance(int n, int m, double **A) {
    double d = 0;
    double max = 0;

    for (int j = 0; j < m-1; j++) {
        for (int p = j+1; p < m; p++) {
            d = 0;
            for (int i = 0; i < n; i++) {
                d += (A[i][j] - A[i][p]) * (A[i][j] - A[i][p]);
            }
            d = sqrt(d);

            if (d > max) {
                max = d;
            }

        }
    }
    return max;
}

void contribuciones(int n, int r, double **eigenvectores, double *V_0){
    double a_m;                           // Calcula ponderacion de vector
    for (int i=0; i<r; i++){
        a_m = 0;                          // Inicializo producto punto
        for (int j=0; j<n; j++) {
            a_m += eigenvectores[i][j]*V_0[j];
        } 
        for (int k=0; k<n; k++){
            V_0[k] -= a_m*eigenvectores[i][k];// Quito Contrubuciones
        }
    }
}

void eigenplot_gnu(char* name0){
    FILE * Grafica= NULL; 
 	//Graficar archivo x con lineas
    char name[80];                                                   
    
    sprintf(name,"%s%s%s","plot\"",name0,"\"using 1:2 with lines");

    Grafica = popen("gnuplot -persist", "w"); 

    fprintf(Grafica,"%s\n",name);


    fclose(Grafica);
}
